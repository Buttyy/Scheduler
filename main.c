#include "scheduler.h"

int main(void)
{
    Task task[MAX_TASK];    // タスクの配列
    int N;                  // タスク数
    int roundrobin;         // ラウンドロビンの定時間

    printf("===== Scheduler =====\n");
    if (!setTask(task, &N, &roundrobin))
        return 0;

    // スケジューラ
    Queue *Aqueue;                  // 到着順の待ち行列リスト
    Queue *Pqueue;                  // 処理時間順の待ち行列リスト
    Queue *Rqueue;                  // ラウンドロビンの待ち行列リスト
    Queue *Alast, *Plast, *Rlast;   // それぞれの待ち行列の最後尾
    int arrive = 0;                 // 次に到着するタスク
    int time = 1;                   // 時刻
    int step;                       // ラウンドロビンでの1つのタスクの実行時間
    Aqueue = Pqueue = Rqueue = Alast = Plast = Rlast = NULL;

    printf("\n--- シミュレーション ---\n");
    printf("START\n");
    printf("時刻 |   到着順   | 処理時間順 | ラウンドロビン\n");

    while (1) {
        // タスクの到着
        while (arrive < N && time-1 == task[arrive].arrival)
            taskArrive(task, &Aqueue, &Pqueue, &Rqueue, &Alast, &Plast, &Rlast, arrive++);

        // 終了判定
        if (Aqueue == NULL && Pqueue == NULL && Rqueue == NULL)
            break;

        printf("%4d | ", time);
        
        // 到着順
        if (Aqueue == NULL) {
            printf("           | ");
        } else {
            if (Aqueue->status == 0)
                Aqueue->status = 1;
            ++(Aqueue->progress);
            if (Aqueue->progress == Aqueue->task->cost) {
                printf("Task:%s fin| ", Aqueue->task->name);
                Aqueue->task->Afinish = time;
                if (Aqueue->next == NULL)
                    Alast = NULL;
                Aqueue = Aqueue->next;
            } else {
                printf("Task:%s    | ", Aqueue->task->name);
            }
        }
        
        // 処理時間順
        if (Pqueue == NULL) {
            printf("           | ");
        } else {
            if (Pqueue->status == 0)
                Pqueue->status = 1;
            ++(Pqueue->progress);
            if (Pqueue->progress == Pqueue->task->cost) {
                printf("Task:%s fin| ", Pqueue->task->name);
                Pqueue->task->Pfinish = time;
                if (Pqueue->next == NULL)
                    Plast = NULL;
                Pqueue = Pqueue->next;
            } else {
                printf("Task:%s    | ", Pqueue->task->name);
            }
        }
        
        // ラウンドロビン
        if (Rqueue == NULL) {
            printf("\n");
        } else {
            if (Rqueue->status == 0) {
                Rqueue->status = 1;
                step = 0;
            }
            ++step;
            ++(Rqueue->progress);
            if (Rqueue->progress == Rqueue->task->cost) {
                printf("Task:%s fin\n", Rqueue->task->name);
                Rqueue->task->Rfinish = time;
                if (Rqueue->next == NULL)
                    Rlast = NULL;
                Rqueue = Rqueue->next;
            } else if (step == roundrobin) {
                printf("Task:%s\n", Rqueue->task->name);
                Rqueue->status = 0;
                Rlast->next = Rqueue;
                Rlast = Rlast->next;
                Rqueue = Rqueue->next;
                Rlast->next = NULL;
            } else {
                printf("Task:%s\n", Rqueue->task->name);
            }
        }

        ++time;
    }
    printf("END\n");

    // 応答時間
    double Asum, Psum, Rsum;    // 合計値
    int Amin, Pmin, Rmin;       // 最小値
    int Amax, Pmax, Rmax;       // 最大値
    Asum = Psum = Rsum = 0.0;
    Amin = Pmin = Rmin = MAX_COST;
    Amax = Pmax = Rmax = 0;

    printf("\n--- 応答時間 ---\n");
    printf("名前 |   到着順   | 処理時間順 | ラウンドロビン\n");
    for (int i=0; i<N; ++i) {
        int Ares = task[i].Afinish-task[i].arrival;
        int Pres = task[i].Pfinish-task[i].arrival;
        int Rres = task[i].Rfinish-task[i].arrival;
        printf("  %s | %10d | %10d | %10d\n", task[i].name, Ares, Pres, Rres);
        Asum += Ares;
        Psum += Pres;
        Rsum += Rres;
        if (Ares < Amin) Amin = Ares;
        if (Pres < Pmin) Pmin = Pres;
        if (Rres < Rmin) Rmin = Rres;
        if (Ares > Amax) Amax = Ares;
        if (Pres > Pmax) Pmax = Pres;
        if (Rres > Rmax) Rmax = Rres;
    }

    printf("\n--- 比較 ---\n");
    printf("       |   到着順   | 処理時間順 | ラウンドロビン\n");
    printf("平均値 | %10.2f | %10.2f | %10.2f\n", Asum/N, Psum/N, Rsum/N);
    printf("最小値 | %10d | %10d | %10d\n", Amin, Pmin, Rmin);
    printf("最大値 | %10d | %10d | %10d\n\n", Amax, Pmax, Rmax);

    return 0;
}
