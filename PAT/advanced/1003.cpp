// 求最短路径的个数, 同时求点权值最大的最短路径
// 测试点较小, DFS也不会超时
// #include <cstdio>
// #include <algorithm>
// #include <vector>
// #include <map>
// using namespace std;
// int src, dest;
// int wVex[512];
// int wArc[512][512];
// vector<int> arc[512];
// bool visit[512];
// map<int, int> cnt;
// map<int, int> maxW;
// void dfs(int vex, int dis, int w)
// {
//     if (vex == dest) 
//     {
//         cnt[dis]++;
//         maxW[dis] = max(maxW[dis], w);
//         return ; // 搜到解回溯
//     }
//     visit[vex] = true; // 防止再走回来
//     for(int i = 0; i < arc[vex].size(); ++i) 
//     {
//         int to = arc[vex][i];
//         if (!visit[to]) 
//         {
//             dfs(to, dis+wArc[vex][to], w+wVex[to]);
//         }
//     }
//     visit[vex] = false;
// }
// int main()
// {
//     int nVex, nArc;
//     scanf("%d %d %d %d", &nVex, &nArc, &src, &dest);
//     for(int i = 0; i < nVex; ++i) 
//     {
//         scanf("%d", &wVex[i]);
//     }
//     for(int i = 0; i < nArc; ++i) 
//     {
//         int start, end, weight;
//         scanf("%d %d %d", &start, &end, &weight);
//         arc[start].push_back(end);
//         arc[end].push_back(start);
//         wArc[start][end] = weight;
//         wArc[end][start] = weight;
//     }
//     dfs(src, 0, wVex[src]);
//     map<int, int>::iterator it = cnt.begin();
//     printf("%d ", it->second);
//     it = maxW.begin();
//     printf("%d\n", it->second);
//     return 0;
// }

#include <cstdio>
#include <cstdlib>
#include <climits>

const int MAX = 501;

int wei[MAX],visit[MAX],map[MAX][MAX];

int mind,cnt,maxt,n;

void init(int n){
	int i,j;

	for(i=0;i<n;++i){
		visit[i] = 0;
		for(j=0;j<n;++j){
			map[i][j]=INT_MAX;
		}
	}
}

void dfs(int p,const int end,int dist,int weit){
	if(p==end){
		if(dist<mind){
			cnt = 1;
			mind=dist;
			maxt = weit;
		}else if(dist==mind){
			++cnt;
			if(maxt<weit){
				maxt = weit;
			}
		}
		return;
	}

	int i;

	if(dist>mind)return;//这个地方不剪枝的话最后一个case过不去

	for(i=0;i<n;++i){
		if(visit[i]==0 && map[p][i]!=INT_MAX){
			visit[i] = 1;
			dfs(i,end,dist+map[p][i],weit+wei[i]);
			visit[i] = 0;
		}
	}

}

int main(){
	int m,st,end,x,y,d,i;
	mind = INT_MAX;
	cnt = 0;

	scanf("%d %d %d %d",&n,&m,&st,&end);
	init(n);
	for(i=0;i<n;++i){
		scanf("%d",&wei[i]);
	}
	while(m--){
		scanf("%d %d %d",&x,&y,&d);
		if(map[x][y]>d){
			map[x][y] = map[y][x] = d;
		}
	}
	dfs(st,end,0,wei[st]);

	printf("%d %d\n",cnt,maxt);
	return 0;
}
