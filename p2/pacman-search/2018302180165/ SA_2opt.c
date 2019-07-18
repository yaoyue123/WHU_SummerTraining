#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "queue.h"
typedef struct {
    int x;
    int y;
} Point;
char *bfs(game_state_t state, int start_x, int start_y, int end_x, int end_y, int *dis, int **location, int *bvisit) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        visit[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++)
            visit[i][j] = 0;
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = start_x;
    elem.y = start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if(elem.x >= 0 && elem.x < state.n
            && elem.y >= 0 && elem.y < state.m
            && visit[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == end_x && elem.y == end_y) {
                    int i = q->rear;
                    (*dis) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {
                        if(state.grid[q->data[i].x][q->data[i].y] == 1) {//如果路上有食物被吃 
                            bvisit[location[q->data[i].x][q->data[i].y]] = 1;//将这个食物置为已访问
                        }
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++)
                        free(visit[i]);
                    free(visit);
                    DestroyQueue(q);
                    return path;
                }
            }
        }
    }
    free(path);
    for(int i = 0; i < state.n; i++) {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
    return NULL;
}
void greedy(game_state_t state, int **location, int *seq) {//通过贪心初始化吃豆子顺序
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
      visit[i] = malloc(sizeof(int) * state.m);
      for(int j = 0; j < state.m; j++) {
          visit[i][j] = 0;
      }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = state.start_x;
    elem.y = state.start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    int point_1 = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if(elem.x >= 0 && elem.x < state.n
            && elem.y >= 0 && elem.y < state.m
            && visit[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(state.food[elem.x][elem.y] == 1) {
                    seq[point_1] = location[elem.x][elem.y];
                    point_1++;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    for(int i = 0; i < state.n; i++) {
                        for(int j = 0; j < state.m; j++)
                            visit[i][j] = 0;
                    }
                    visit[elem.x][elem.y] = 1;
                    break;
                }
            }
        }
    }
    free(path);
    for(int i = 0; i < state.n; i++)
        free(visit[i]);
    free(visit);
    DestroyQueue(q);
}
int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(146146146);
    Point *bean;//用来记录豆子位置的数组
    int beanNum = 0;//用来记录豆子个数的数组
    int **location = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    bean = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {//如果这个地方有食物，就把这个食物位置加入数组
                bean[beanNum].x = i;
                bean[beanNum].y = j;
                location[i][j] = beanNum;//更新地址表
                beanNum++;
            }
        }
    }
    int *startList = malloc(sizeof(int) * beanNum);//用于存储起点到豆子的距离
    int **disList = malloc(sizeof(int *) * beanNum);//用于存储豆子之间的距离，避免重复计算
    for(int i = 0; i < beanNum; i++) {
        startList[i] = -1;
        disList[i] = malloc(sizeof(int) * beanNum);
        for(int j = 0; j < beanNum; j++) {
            disList[i][j] = -1;
        }
    }
    int *seq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录吃豆子的顺序
    greedy(state, location, seq);//初始化吃豆子顺序
    int *visit = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录豆子是否已经被吃，要求每次之前必须全为0
    memset(visit, 0, sizeof(int) * beanNum);
    int dis;
    int dismin = 0;
    char *path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dis, location, visit);
    dismin += dis;
    free(path);
    startList[seq[0]] = dis;
    for(int i = 1; i < beanNum; i++) {
        int k = i;
        while(k < beanNum) {
            if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == beanNum)
            break;//说明豆子已经被吃光，跳出循环
        path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[k]].x, bean[seq[k]].y, &dis, location, visit);
        free(path);
        dismin += dis;
        disList[seq[i - 1]][seq[k]] = disList[seq[k]][seq[i - 1]] = dis;
    }
    //在下面用SA对路径进行调整
    int kmax = 3000000;//降温时间
    double temp = 10;//初始温度
    for(int k = 0; k <= kmax; k++) {
        double T = (double)temp / (k + 1);
        int startPoint = rand() % beanNum;
        int endPoint = rand() % beanNum;
        if(startPoint >= endPoint) {
            k--;
            continue;
        }
        int *newseq = (int *)malloc(sizeof(int) * beanNum);
        //对原来序列进行翻转操作
        for(int i = 0; i < startPoint; i++)
            newseq[i] = seq[i];
        for(int i = startPoint; i <= endPoint; i++)
            newseq[i] = seq[startPoint + endPoint - i];
        for(int i = endPoint + 1; i < beanNum; i++)
            newseq[i] = seq[i];
        int dis;
        int dissum = 0;
        memset(visit, 0, sizeof(int) * beanNum);
        if(startList[newseq[0]] != -1) {
            dissum += startList[newseq[0]];
        } else {
            path = bfs(state, state.start_x, state.start_y, bean[newseq[0]].x, bean[newseq[0]].y, &dis, location, visit);
            free(path);
            dissum += dis;
            startList[newseq[0]] = dis;
        }
        for(int i = 1; i < beanNum; i++) {
            int k = i;
            while(k < beanNum) {
                if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                    k++;
                else
                    break;
            }
            if(k == beanNum)
                break;//说明豆子已经被吃光，跳出循环
            if(disList[newseq[i - 1]][newseq[k]] != -1)
                dissum += disList[newseq[i - 1]][newseq[k]];
            else {
                path = bfs(state, bean[newseq[i - 1]].x, bean[newseq[i - 1]].y, bean[newseq[k]].x, bean[newseq[k]].y, &dis, location, visit);
                free(path);
                dissum += dis;
                disList[newseq[i - 1]][newseq[k]] = disList[newseq[k]][newseq[i - 1]] = dis;
            }
        }
        if(exp((double)(dismin - dissum) / T ) > (double)1.0 * (rand() % 10000) / 9999) {
            dismin = dissum;
            memcpy(seq, newseq, sizeof(int) * beanNum);
        }
        free(newseq);
    }
    //
    memset(visit, 0, sizeof(int) * beanNum);
    path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dis, location, visit);
    printf("%s", path);
    free(path);
    for(int i = 1; i < beanNum; i++) {
        int k = i;
        while(k < beanNum) {
            if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == beanNum)
            break;//说明豆子已经被吃光，跳出循环
        path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[k]].x, bean[seq[k]].y, &dis, location, visit);
        printf("%s", path);
        free(path);
	}
    free(bean);
    free(seq);
    for(int i = 0; i < state.n; i++)
        free(location[i]);
    free(location);
    for(int i = 0; i < beanNum; i++)
        free(disList[i]);
    free(disList);
    free(startList);
    free(visit);
  // 
  destroy(&state);
  return 0;
}
