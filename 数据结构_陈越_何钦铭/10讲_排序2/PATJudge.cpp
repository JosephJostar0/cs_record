#include <algorithm>
#include <iostream>
#include <vector>
int ranks[6], N, K, M;
class Stu {
public:
    int sum, level[6], nice, sno;
    void getLevel(int t);
    void print();
    Stu() { sno = 0, sum = 0, nice = 0, std::fill(level, level + 6, -2); }
} student[10001];
std::vector<int> vec;

void Stu::getLevel(int t) {
    int id, rank;
    scanf("%d%d", &id, &rank);
    if (rank > level[id]) {
        if (level[id] > 0)
            sum -= level[id];
        level[id] = rank;
        if (level[id] >= 0) {
            sum += level[id];
            if (sno == 0)
                vec.push_back(t);
            sno = t;
        }
        if (level[id] == ranks[id])
            nice++;
    }
}

void Stu::print() {
    printf("%05d %d", sno, sum);
    for (int i = 1; i <= K; i++) {
        if (level[i] >= 0)
            printf(" %d", level[i]);
        else if (level[i] == -2)
            printf(" -");
        else
            printf(" 0");
    }
}

bool cmp(int x, int y) {
    Stu a = student[x], b = student[y];
    if (a.sum != b.sum)
        return a.sum > b.sum;
    if (a.nice != b.nice)
        return a.nice > b.nice;
    return x < y;
}

int main() {
    int i, t;
    scanf("%d%d%d", &N, &K, &M);
    for (i = 1; i <= K; i++)
        scanf("%d", ranks + i);
    for (i = 0; i < M; i++) {
        scanf("%d", &t);
        student[t].getLevel(t);
    }
    std::sort(vec.begin(), vec.end(), cmp);
    printf("%d ", 1), student[vec[0]].print();
    for (i = 1, t = 1; i < vec.size(); i++) {
        if (student[vec[i]].sum < student[vec[i - 1]].sum)
            t = i + 1;
        printf("\n%d ", t), student[vec[i]].print();
    }
    return 0;
}
