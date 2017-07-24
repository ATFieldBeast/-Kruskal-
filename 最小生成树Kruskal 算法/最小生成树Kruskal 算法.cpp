// 最小生成树Kruskal 算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 

typedef struct {
	int vex;
	int gno;
}TVex;

typedef struct {
	int vh, vt;
	int cost;
	int flag;
}TEdge;

typedef struct {
	TVex *pv;
	TEdge *pe;
	int nv, ne;
}TGragh, *PGragh;

void Read_file(PGragh G, char *fname);
void Init_gragh(PGragh G);
void Kruskal_mst(PGragh G);
void PrintGragh(PGragh G);
void PrintMST(PGragh G);

void Read_file(PGragh G, char *fname) {
	FILE *pFile = NULL;
	int i, j;
	int vh, vt;
	int exist;
	int fvh, fvt, fcost;
	pFile = fopen(fname, "r");
	printf("File Opens Successfully\n\n");
	while (!feof(pFile)) {
		exist = 0;
		fscanf(pFile, "%d\t%d\t%d\n", &fvh, &fvt, &fcost);
		for (i = 0; i<G->ne; i++) {
			if (G->pe[i].vh == fvh && G->pe[i].vt == fvt) {
				exist = 1;
			}
			if (G->pe[i].vh == fvt && G->pe[i].vt == fvh) {
				exist = 1;
			}
		}
		if (!exist) {
			G->pe[G->ne].vh = fvh;
			G->pe[G->ne].vt = fvt;
			G->pe[G->ne].cost = fcost;
			G->pe[G->ne].flag = 0;
			G->ne++;
		}

	}
	for (i = 0; i<G->ne; i++) {
		vh = G->pe[i].vh;
		vt = G->pe[i].vt;
		exist = 0;
		for (j = 0; j<G->nv; j++) {
			if (vh == G->pv[j].gno) {
				exist = 1;
				break;
			}
		}
		if (!exist) {
			G->pv[G->nv].gno = vh;
			G->pv[G->nv].vex = vh;
			G->nv++;
		}
		exist = 0;
		for (j = 0; j<G->nv; j++) {
			if (vt == G->pv[j].gno) {
				exist = 1;
				break;
			}
		}
		if (!exist) {
			G->pv[G->nv].gno = vt;
			G->pv[G->nv].vex = vt;
			G->nv++;
		}
	}
	fclose(pFile);
}

void Init_gragh(PGragh G) {
	G->pv = (TVex*)malloc(sizeof(TVex)*MAX);
	G->pe = (TEdge*)malloc(sizeof(TEdge)*MAX);
	G->nv = 0;
	G->ne = 0;
}

void Kruskal_mst(PGragh G) {
	int i, min, idx, m, n, g, count = 1;
	while (count < G->nv) {
		min = MAX;
		for (i = 0; i<G->ne; ++i) {
			if (G->pe[i].cost < min && G->pe[i].flag == 0) {
				min = G->pe[i].cost;
				idx = i;
			}
		}
		m = G->pe[idx].vh;
		n = G->pe[idx].vt;
		if (G->pv[m].gno != G->pv[n].gno) {
			G->pe[idx].flag = 1;
			count++;
			g = G->pv[n].gno;
			for (i = 1; i <= G->nv; i++) {
				if (G->pv[i].gno == g) {
					G->pv[i].gno = G->pv[m].gno;
				}
			}
		}
		else {
			G->pe[idx].flag = -1;
		}
	}
}

void PrintGragh(PGragh G) {
	int i;
	printf("The Gragh is\n");
	printf("vh vt cost\n");
	for (i = 0; i<G->ne; i++) {
		printf("%d  %d  %d\n", G->pe[i].vh, G->pe[i].vt, G->pe[i].cost);
	}

}

void PrintMST(PGragh G) {
	int i;
	printf("vh vt weight\n");
	for (i = 0; i<G->ne; i++) {
		if (G->pe[i].flag == 1) {
			printf("%d  %d  %d\n", G->pe[i].vh, G->pe[i].vt, G->pe[i].cost);
		}

	}
}

int main() {
	PGragh G;
	char *fname = "E:/graph.txt";

	Init_gragh(G);
	Read_file(G, fname);
	PrintGragh(G);
	Kruskal_mst(G);
	printf("\n");
	printf("MST:\n");
	PrintMST(G);

	return 0;
}