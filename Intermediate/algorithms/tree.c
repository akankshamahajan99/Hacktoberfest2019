#include <stdio.h> //fprintf
#include <stdlib.h> //malloc
#include <string.h> //string

typedef struct data {
	char name[16];
	int marks;
} data;
typedef struct node {
	data d;
	struct node *left, *right;
} node;
typedef node *tree;
void init(tree *t);
void insert(tree *t, data store);
void inorder_store(tree t, FILE *fp);


void init(tree *t) {
	*t = NULL;
	return;
}
void insert(tree *t, data store) {
	int result;
	node *temp, *mover, *prev;
	temp = (node *)malloc(sizeof(node));
	temp->d = store;
	temp->right = temp->left = NULL;
	mover = *t;
	prev = NULL;
	if(mover == NULL) {
		*t = temp;
		return;
	}
	while(mover != NULL) {
		prev = mover;
		result = strcmp(mover->d.name, store.name);
		if(result > 0)
			mover = mover->left;
		else if(result < 0)
			mover = mover->right;
		//repeated not accepted
		else
			return;
	}
	result = strcmp(prev->d.name, store.name);
	if(result > 0)
		prev->left = temp;
	else
		prev->right = temp;
	return;
}
void inorder_store(tree t, FILE *fp) {
	//lnr
	if(t) {
		inorder_store(t->left, fp);
		fprintf(fp, "%s, %d\n", t->d.name, t->d.marks);
		inorder_store(t->right, fp);
	}
}


int main(int argv, char *argc[]) {
	data d;
	tree t;
	FILE *creatBT, *newfil;
	if(argv < 3) {
		fprintf(stderr, "Less arguments, Try ./try <filename1.txt> <filename2.txt> <filename3.txt>\n");
		return 0;
	}
	creatBT = fopen(argc[1], "r");
	if(creatBT == NULL)
		return 0;
	init(&t);
	while(1) {
		if(fscanf(creatBT, "%[^,]s", d.name) == -1)
			break;
		getc(creatBT);
		fscanf(creatBT, "%d", &d.marks);
		getc(creatBT);
		insert(&t, d);
	}
	fclose(creatBT);
	newfil = fopen(argc[2], "w");
	inorder_store(t, newfil);
	fclose(newfil);
	return 0;
}