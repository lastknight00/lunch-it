#include<cstdio>
#include<stdlib.h>
#include<string.h>
#include<queue>
#define ARRSIZE 10
#define MAX_VAL 100
#define MIN(x,y) ((x) > (y)) ? (y) : (x)
#define MAX(x,y) ((x) > (y)) ? (x) : (y)
using namespace std;
void print_arr(int*, int);
void pigeonhole(int*, int, bool);
void radix(int*, int, bool);
void counting(int*, int, bool);
int main(){
	//int data[ARRSIZE] = {1,2,3,4,5,6,7,8,9,10};
	//pigeonhole(data, ARRSIZE, false);

	//int data[ARRSIZE] = {119,236,54,445,21,56,77,97,75,51};
	//radix(data, ARRSIZE, true);

	int data[ARRSIZE] = {9, 1, 5, 9, 2, 4, 5, 2, 1, 3};
	counting(data, ARRSIZE, false);
	
	print_arr(data, ARRSIZE);
}
void pigeonhole(int* data, int size, bool asc){
	int max_val = -1, min_val = 1<<30;
	for(int i = 0; i < size; i++) {
		max_val = MAX(max_val, data[i]);
		min_val = MIN(min_val, data[i]);
	}
	int* cnt = (int*)calloc(size, sizeof(int));
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < size; i++) {
		cnt[data[i] - min_val]++;
	}
	int offset = max_val - min_val;
	int point = 0;
	if(asc) {
		for(int i = 0; i <= offset; i++){
			while(cnt[i]--) {
				data[point++] = min_val + i;
			}
		}
	} else {
		for(int i = offset; i >= 0; i--){
			while(cnt[i]--) {
				data[point++] = min_val + i;
			}
		}
	}
	free(cnt);
}
void radix(int* data, int size, bool asc) {
	int m = 0;
	int max_val = 0;
	queue<int> q[10];
	for(int i = 0; i < size; i++) max_val = MAX(max_val, data[i]);
	while(max_val) {
		m++;
		max_val /= 10;
	}
	int div = 1;
	if(asc) {
		for(int i = 0; i < m; i++) {
			for(int j = 0 ; j < size; j++) {
				q[(data[j] / div) % 10].push(data[j]);
			}
			int point = 0;
			for(int j = 0; j < 10; j++) {
				while(!q[j].empty()) {
					data[point++] = q[j].front();
					q[j].pop();
				}
			}
			div *= 10;
		}
	} else {
		for(int i = 0; i < m; i++) {
			for(int j = 0 ; j < size; j++) {
				q[(data[j] / div) % 10].push(data[j]);
			}
			int point = 0;
			for(int j = 9; j >= 0; j--) {
				while(!q[j].empty()) {
					data[point++] = q[j].front();
					q[j].pop();
				}
			}
			div *= 10;
		}
	}
}
void counting(int* data, int size, bool asc) {
	int cnt[MAX_VAL];
	int* retval = (int*)calloc(sizeof(int), size);
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < size; i++) cnt[data[i]]++;
	for(int i = 1; i < MAX_VAL; i++) cnt[i] += cnt[i - 1];
	if(asc){
		for(int i = 0; i < size; i++) {
			retval[cnt[data[i]] - 1] = data[i];
			cnt[data[i]]--;
		}
	} else {
		for(int i = size - 1; i >=0; i--) {
			retval[size - (cnt[data[i]])] = data[i];
			cnt[data[i]]--;
		}	
	}
	memcpy(data, retval, sizeof(int) * size);
}
void print_arr(int* data, int size){
	for(int i = 0; i < size; i++) printf("%d ", data[i]);
	printf("\n");
}
