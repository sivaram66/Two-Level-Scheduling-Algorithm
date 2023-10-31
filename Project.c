#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int priority;
    int burst_time;
};

struct Queue {
    struct Process* processes;
    int front, rear;
    int size;
};

int count = 0;
int length = 0;
struct Process ganttchart[50];

struct Process creatingProcess(int id, int priority, int burst_time) {
    struct Process p;
    p.id = id;
    p.priority = priority;
    p.burst_time = burst_time;
    return p;
}

struct Queue creatingQueue(int size) {
    struct Queue q;
    q.size = size;
    q.processes = (struct Process*)malloc(size * sizeof(struct Process));
    q.rear = q.front = -1;
    return q;
}

int isEmpty(struct Queue* q) {
    return (q->front == -1 && q->rear == -1);
}

int isFull(struct Queue* q) {
    return ((q->rear + 1) % q->size == q->front);
}

void Enqueue(struct Queue* q, struct Process process) {
    if (isFull(q)) {
        printf("Queue is full. Can't enqueue\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
        q->processes[q->rear] = process;
    } else {
        q->rear = (q->rear + 1) % q->size;
        q->processes[q->rear] = process;
    }
}

struct Process Dequeue(struct Queue* q) {
    struct Process empty_process;
    empty_process.id = -1;

    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return empty_process;
    }
    struct Process process = q->processes[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else
        q->front = (q->front + 1) % q->size;

    return process;
}

void executingPriorityQueue(struct Queue* q1, struct Queue* q2) {
    struct Process processesArray[q1->size];
    struct Process tostore;

    while (!isEmpty(q1)) {
        processesArray[count] = Dequeue(q1);
        count++;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (processesArray[j].priority < processesArray[i].priority) {
                struct Process temp = processesArray[i];
                processesArray[i] = processesArray[j];
                processesArray[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        tostore = processesArray[i];
        ganttchart[i] = tostore;
        length++;
    }
    for (int i = 0; i < count; i++) {
        struct Process process = processesArray[i];
        printf("Executing process %d from Queue 1 (Priority: %d)\n", process.id, process.priority);

        process.burst_time -= 2;
        if (process.burst_time == 0) {
            printf("Process %d Executed Completely\n", process.id);
        }

        if (process.burst_time > 0) {
            printf("Process %d Moved to Queue 2\n", process.id);
            Enqueue(q2, process);
        }
    }
}

void executingRoundRobinQueue(struct Queue* q2) {
    struct Process Tostore1;
    while (!isEmpty(q2)) {
        Tostore1 = Dequeue(q2);
        struct Process process = Tostore1;
        printf("Executing process %d from Queue 2 (Round Robin)\n", process.id);
        process.burst_time -= 2;
        ganttchart[count] = Tostore1;
        count++;
        length++;
        if (process.burst_time > 0) {
            Enqueue(q2, process);
        }
    }
}

void displayGanttChart(struct Process* arr, int length) {
    printf("\nGanttChart:\n");
    for (int j = 0; j < length; j++) {
        printf("----- ");
    }
    printf("\n|");
    for (int i = 0; i < length; i++) {
        printf("  P%d |", arr[i].id);
    }
    printf("\n");
    for (int j = 0; j < length; j++) {
        printf("----- ");
    }
}

int main() {
    struct Queue q1 = creatingQueue(50);
    struct Queue q2 = creatingQueue(50);

    struct Process p1 = creatingProcess(1, 1, 6);
    struct Process p2 = creatingProcess(2, 2, 2);
    struct Process p3 = creatingProcess(3, 0, 8);

    Enqueue(&q1, p1);
    Enqueue(&q1, p2);
    Enqueue(&q1, p3);

    executingPriorityQueue(&q1, &q2);
    executingRoundRobinQueue(&q2);
    displayGanttChart(ganttchart, length);

    return 0;
}
