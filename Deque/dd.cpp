#include <stdio.h>
#include <stdlib.h>

struct item{
	int data;
	struct item *next, *prev;
};

struct deque{
	struct item *first, *last;
};

void PushDeque(struct deque *dq, int val)
{
	struct item *tmp = malloc(sizeof(struct item));
	tmp->data = val;
	tmp->next = dq->first;
	tmp->prev = NULL;
	if(dq->first)
		dq->first->prev = tmp;
	else
		dq->last = tmp;
	dq->first = tmp;
}

int PopDeque(struct deque *dq)
{
	if(!dq->first)
		return 0;
	struct item *tmp = dq->first;
	int val = tmp->data;
	dq->first = tmp->next;
	if(dq->first)
		dq->first->prev = NULL;
	else
		dq->last = dq->first;
	free(tmp);
	return val;
}

int GetDeque(struct deque *dq)
{
	if(!dq->last)
		return 0;
	struct item *tmp = dq->last;
	int val = tmp->data;
	dq->last = tmp->prev;
	if(dq->last)
		dq->last->next = NULL;
	else
		dq->first = dq->last;
	free(tmp);
	return val;
}

void AddDeque(struct deque *dq, int val)
{
	struct item *tmp = malloc(sizeof(struct item));
	tmp->data = val;
	tmp->prev = dq->last;
	tmp->next = NULL;
	if(dq->last)
		dq->last->next = tmp;
	else
		dq->first = tmp;
	dq->last = tmp;
}

void PrintDeque(struct deque dq)
{
	while(dq.first){
		printf("%d ", dq.first->data);
		dq.first = dq.first->next;
	}
	printf("\n");
}

void InitDeque(struct deque *dq)
{
	dq->first = dq->last = NULL;
}

int main()
{
	struct deque dq;
	InitDeque(&dq);
	printf("%d\n", GetDeque(&dq));
	printf("%d\n", GetDeque(&dq));
	printf("%d\n", PopDeque(&dq));
	printf("%d\n", PopDeque(&dq));
	PushDeque(&dq, 3);
	PushDeque(&dq, 5);
	PushDeque(&dq, 7);
	AddDeque(&dq, 3);
	AddDeque(&dq, 5);
	AddDeque(&dq, 7);
	PrintDeque(dq);
	printf("%d\n", GetDeque(&dq));
	printf("%d\n", GetDeque(&dq));
	PrintDeque(dq);
	printf("%d\n", PopDeque(&dq));
	printf("%d\n", PopDeque(&dq));
	PrintDeque(dq);
	PushDeque(&dq, 9);
	PushDeque(&dq, 1);
	PrintDeque(dq);

	return 0;
}
