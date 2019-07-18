#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int dx[4]={0,1,-1,0};//s,w,d,a
int dy[4]={-1,0,0,1};

char b[]={'W','S','N','E'};
int ans=0x3f3f3f3f;

bool vis[150][150];
int path[100];
void dfs(int x,int y,int cnt,game_state_t state){
    
	if(x==state.goal_x&&y==state.goal_y){
		ans= cnt<ans? cnt:ans;
		return;
	}
	if(cnt >= ans){
		return;
	}
	vis[x][y]=1;
	for(int i=0;i<4;i++){

		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx >= 0&&tx<state.n&&ty>=0&&ty<state.m&&
		state.grid[tx][ty]!=1&&vis[tx][ty]==0){
        printf("%c",b[i]);
        dfs(tx,ty,cnt+1,state);
        printf("%c",b[3-i]);
		}
	}
	vis[x][y]=0;
}
int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  dfs(state.start_x, state.start_y,0,state);
  //printf("SSWSWWSW\n");
  
  // 
  destroy(&state);
  return 0;
}
