#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TASK 100
#define MAX_NAME 3
#define MAX_COST 20

typedef struct Task{
    char name[MAX_NAME];    // 名前
    int arrival;            // 到着時刻
    int cost;               // 処理時間
    int Afinish;            // 到着順での終了時刻
    int Pfinish;            // 処理時間順での終了時刻
    int Rfinish;            // ラウンドロビンでの終了時刻
} Task;

typedef struct Queue{
    Task *task;             // タスク
    int progress;           // 進行時間
    int status;             // 状態(実行可能:0 実行:1)
    struct Queue *next;     // 次に待っているタスク
} Queue;

int setTask(Task *task, int *N, int *roundrobin);
Queue* generateQueue(Task *task);
void taskArrive(Task *task, Queue **Aqueue, Queue **Pqueue, Queue **Rqueue, Queue **Alast, Queue **Plast, Queue **Rlast, int arrive);

#endif /* SCHEDULER_H_ */
