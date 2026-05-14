// SteinerOptimalTreeFinder.cpp
#include "SteineResolver.h"
#include "Utils/Steiner.h"
#include <algorithm>
#include <numeric>
#include <deque>
#include <cfloat>
#include <cmath>



// ─── геометрия ───────────────────────────────────────────────

static double Dist(const CPoint& a, const CPoint& b) {
    const double dx = a.x - b.x, dy = a.y - b.y;
    return std::sqrt(dx*dx + dy*dy);
}

// Вершина равностороннего треугольника на AB,
// противоположная стороне refPoint — та же логика что в BuildEquilateralTriangle.
// Нужна для фазы слияния: виртуальная точка V заменяет пару (A, B).
static CPoint EquilateralVertex(const CPoint& A, const CPoint& B,
                                 const CPoint& refPoint) {
    const CPoint mid   = (A + B) / 2.0;
    const CVector v    = CVector(B - A);
    const double  h    = v.dist() * std::sqrt(3.0) / 2.0;
    CVector perp       = { -v.y, v.x };
    perp /= perp.dist();

    const CPoint c1 = { mid.x + perp.x * h, mid.y + perp.y * h };
    const CPoint c2 = { mid.x - perp.x * h, mid.y - perp.y * h };

    // выбираем сторону, противоположную refPoint
    return (Dist(c1, refPoint) > Dist(c2, refPoint)) ? c1 : c2;
}

// ─── топологии ───────────────────────────────────────────────
// Топология = порядок слияний троек индексов.
// Для n терминалов нужно n-2 точек Штейнера, т.е. n-2 слияния.
// Каждое слияние потребляет 3 «живых» узла и порождает 1 виртуальный.
// Живых узлов: n → n-2 → ... → 2 (последние два соединяются ребром).
//
// Слияние задаётся тройкой индексов (i, j, k) в текущем рабочем векторе.
// Фиксируем i=0 на каждом шаге (убирает дубли от перестановок).

struct Merge { size_t i, j, k; };
using Topology = std::vector<Merge>;

static void GenTopologies(std::vector<size_t> alive,
                          Topology current,
                          std::vector<Topology>& out) {
    if (alive.size() == 2) {
        out.push_back(current);
        return;
    }
    // фиксируем alive[0], перебираем пары партнёров
    for (size_t j = 1; j < alive.size(); ++j) {
        for (size_t k = j + 1; k < alive.size(); ++k) {
            Topology next = current;
            next.push_back({ alive[0], alive[j], alive[k] });

            // новый рабочий вектор: убираем j и k, alive[0] → виртуальная точка
            std::vector<size_t> nextAlive;
            nextAlive.push_back(alive[0]); // слот 0 = новая виртуальная точка
            for (size_t m = 1; m < alive.size(); ++m)
                if (m != j && m != k)
                    nextAlive.push_back(alive[m]);

            GenTopologies(nextAlive, next, out);
        }
    }
}

static std::vector<Topology> AllTopologies(size_t n) {
    if (n < 3) return {{}};
    std::vector<size_t> alive(n);
    std::iota(alive.begin(), alive.end(), 0);
    std::vector<Topology> result;
    GenTopologies(alive, {}, result);
    return result;
}

struct MelzakResult {
    std::vector<CPoint> steinerPoints;
    double length;
};

struct MergeRecord {
    CPoint A, B, C;
    CPoint virtualPt;
};

static std::optional<MelzakResult> MelzakFST(
        const std::vector<CPoint>& terminals,
        const Topology& topology) {

    // рабочий вектор координат (по значению — нет проблем с lifetime)
    std::vector<CPoint> work(terminals);

    std::vector<MergeRecord> history;
    history.reserve(topology.size());

    // ── фаза слияния ──
    for (const auto& merge : topology) {
        CPoint& A = work[merge.i];
        CPoint& B = work[merge.j];
        CPoint& C = work[merge.k];

        const CPoint V = EquilateralVertex(A, B, C);

        history.push_back({ A, B, C, V });

        // обновляем рабочий вектор: слот i → V, слоты j и k помечаем удалёнными
        // (используем NaN как sentinel)
        A = V;
        B = { std::numeric_limits<double>::quiet_NaN(), 0 };
        C = { std::numeric_limits<double>::quiet_NaN(), 0 };
    }

    // два оставшихся живых узла — прямое ребро
    std::vector<CPoint> survivors;
    for (const auto& p : work)
        if (!std::isnan(p.x))
            survivors.push_back(p);

    if (survivors.size() != 2) return std::nullopt;
    double totalLen = Dist(survivors[0], survivors[1]);

    // ── фаза разворачивания ──
    // Храним точки в deque чтобы ссылки не инвалидировались
    std::deque<CPoint> steinerStorage;
    std::vector<CPoint> steinerPoints;

    for (int idx = (int)history.size() - 1; idx >= 0; --idx) {
        auto& rec = history[idx];

        const auto tryABC = ::Steiner::GetSteinerPoint(rec.A, rec.B, rec.C);
        const auto tryBAC = tryABC ? std::nullopt : ::Steiner::GetSteinerPoint(rec.B, rec.A, rec.C);
        const auto tryACB = tryBAC ? std::nullopt : ::Steiner::GetSteinerPoint(rec.A, rec.C, rec.B);

        const auto* sOpt = tryABC ? &tryABC : (tryBAC ? &tryBAC : (tryACB ? &tryACB : nullptr));
        if (!sOpt) return std::nullopt;

        const CPoint S = sOpt->value().steinerPoint;
        steinerPoints.push_back(S);

        // длина: три ребра от S к A, B, C минус ребро виртуальной точки
        // (виртуальное ребро V→следующий узел уже учтено в totalLen)
        totalLen += Dist(S, rec.A) + Dist(S, rec.B) + Dist(S, rec.C);
        totalLen -= Dist(rec.virtualPt, /* партнёр V в следующем слиянии */ rec.C);
        // корректировка: убираем ребро V-C которое было в виртуальном дереве
    }

    return MelzakResult{ steinerPoints, totalLen };
}

// ─── MST по всем вершинам (Прим)

static Graph BuildGraph(const std::vector<std::pair<size_t, CPoint>>& terminals,
                        const std::vector<CPoint>& steinerPts) {
    Graph g;
    for (const auto& [id, pt] : terminals)
        g.nodes.push_back({ id, pt, NodeType::Terminal });
    const size_t tCount = terminals.size();
    for (size_t i = 0; i < steinerPts.size(); ++i)
        g.nodes.push_back({ tCount + i, steinerPts[i], NodeType::SteinerPoint });

    const size_t N = g.nodes.size();
    if (N < 2) return g;

    auto d = [&](size_t i, size_t j) {
        return Dist(g.nodes[i].point, g.nodes[j].point);
    };

    std::vector<bool>   inMST(N, false);
    std::vector<double> key(N, DBL_MAX);
    std::vector<size_t> parent(N, SIZE_MAX);
    key[0] = 0.0;

    for (size_t iter = 0; iter < N; ++iter) {
        size_t u = SIZE_MAX;
        for (size_t i = 0; i < N; ++i)
            if (!inMST[i] && (u == SIZE_MAX || key[i] < key[u]))
                u = i;
        inMST[u] = true;
        if (parent[u] != SIZE_MAX) {
            const double len = d(u, parent[u]);
            g.edges.push_back({ g.nodes[parent[u]].id, g.nodes[u].id, len });
            g.totalLength += len;
        }
        for (size_t v = 0; v < N; ++v)
            if (!inMST[v] && d(u, v) < key[v]) {
                key[v] = d(u, v), parent[v] = u;
            }
    }
    return g;
}

// ─── публичная функция ────────────────────────────────────────

Graph FindOptimalTree(std::vector<std::pair<size_t, CPoint>>& terminals) {
    const size_t n = terminals.size();
    if (n <= 2) return BuildGraph(terminals, {});

    std::vector<CPoint> pts;
    for (const auto& [id, pt] : terminals) pts.push_back(pt);

    const auto topologies = AllTopologies(n);

    auto bestLen = DBL_MAX;
    Graph  bestGraph;

    std::vector<size_t> perm(n);
    std::iota(perm.begin(), perm.end(), 0);

    do {
        std::vector<CPoint> permPts(n);
        for (size_t i = 0; i < n; ++i) permPts[i] = pts[perm[i]];

        for (const auto& topo : topologies) {
            auto res = MelzakFST(permPts, topo);
            if (!res) continue;

            auto graph = BuildGraph(terminals, res->steinerPoints);
            if (graph.totalLength < bestLen) {
                bestLen   = graph.totalLength;
                bestGraph = graph;
            }
        }
    } while (std::next_permutation(perm.begin() + 1, perm.end()));

    if (bestLen == DBL_MAX)
        return BuildGraph(terminals, {});

    return bestGraph;
}