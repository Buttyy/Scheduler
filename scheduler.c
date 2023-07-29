#include "scheduler.h"

// タスクの設定
int setTask(Task *task, int *N, int *roundrobin)
{
    int choice;

    printf("ラウンドロビンの定時間: ");
    scanf("%d", roundrobin);
    printf("タスク数(%d以下): ", MAX_TASK);
    scanf("%d", N);
    if (*N <= 0 || MAX_TASK < *N) {
        printf("無効な入力です\n");
        return 0;
    }

    printf("\n--- タスク生成 ---\n");
    printf("1: 指定\n");
    printf("2: ランダム\n");
    printf("選択: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // 指定
        printf("名前 | 到着時刻 | 処理時間\n");
        for (int i=0; i<*N; ++i) {
            scanf("%s %d %d", task[i].name, &task[i].arrival, &task[i].cost);
            if (task[i].name[1] == '\0') {
                task[i].name[1] = ' ';
                task[i].name[2] = '\0';
            }
        }
    } else if (choice == 2) {
        // ランダム
        printf("名前 | 到着時刻 | 処理時間\n");
        int sum = 0;
        srand((unsigned int)time(NULL));
        for (int i=0; i<*N; ++i) {
            task[i].name[0] = i/10 + '0';
            task[i].name[1] = i%10 + '0';
            task[i].name[2] = '\0';
            if (i == 0) task[i].arrival = 0;
            else        task[i].arrival = task[i-1].arrival + rand()%((sum+1)/2 - task[i-1].arrival);
            task[i].cost = 1 + rand()%MAX_COST;
            sum += task[i].cost;
            printf("%s   | %8d | %8d\n", task[i].name, task[i].arrival, task[i].cost);
        }
    } else {
        printf("無効な入力です\n");
        return 0;
    }

    return 1;
}



// 待ち行列の構造体を生成
Queue* generateQueue(Task *task)
{
    Queue *p = (Queue*)malloc(sizeof(Queue));
    p->task = task;
    p->progress = 0;
    p->status = 0;
    p->next = NULL;
    return p;
}



// タスクの到着
void taskArrive(Task *task, Queue **Aqueue, Queue **Pqueue, Queue **Rqueue, Queue **Alast, Queue **Plast, Queue **Rlast, int arrive)
{
    // 到着順
    if (*Alast == NULL) {
        *Alast = *Aqueue = generateQueue(&task[arrive]);
    } else {
        (*Alast)->next = generateQueue(&task[arrive]);
        *Alast = (*Alast)->next;
    }

    // 処理時間順
    if (*Plast == NULL) {
        *Plast = *Pqueue = generateQueue(&task[arrive]);
    } else if ((*Pqueue)->status == 0 && (*Pqueue)->task->cost > task[arrive].cost) {
        Queue *new = generateQueue(&task[arrive]);
        new->next = *Pqueue;
        *Pqueue = new;
    } else {
        Queue *new = generateQueue(&task[arrive]);
        Queue *tmp = *Pqueue;
        while (tmp->next != NULL && tmp->next->task->cost <= task[arrive].cost) {
            tmp = tmp->next;
        }
        new->next = tmp->next;
        tmp->next = new;
    }
    
    // ラウンドロビン
    if (*Rlast == NULL) {
        *Rlast = *Rqueue = generateQueue(&task[arrive]);
    } else {
        (*Rlast)->next = generateQueue(&task[arrive]);
        *Rlast = (*Rlast)->next;
    }
}
