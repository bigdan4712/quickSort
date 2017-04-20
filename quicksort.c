#include <stdio.h>

int data[100000];

//================================================
// int partition(int data[],int low,int high)
//
//		hole = %ebx
//		low = %esi
//		high = %edx
//		P 	= %ecx


asm(	"		.text							  				\n"
		"		.globl	partition					  				\n"
		"		.type	partition,@function				  		\n"
                                                                                                                                                                                                                                                              
		"partition:								  				\n"
		"		push	%rbp						  			\n"
		"		movq	%rsp,%rbp					  			\n"
		"		movl	(%rdi,%esi,4),%ecx						\n"
		"		movl	%esi, %ebx								\n"
		"		jmp		1f										\n"
		"3:		decl	%edx									\n"
		"2:		cmpl	%edx, %esi								\n"
		"		jg		4f										\n"
		"		cmpl	%ecx,(%rdi,%edx,4)						\n"
		"		jge		3b										\n"
		"4:		cmpl	%edx, %esi								\n"
		"		jg		5f										\n"
		"		











		"1:	cmpl	%edx, %esi								\n"
		"	jl		2b										\n"	

		/* rdi is address of data, esi is low */

		/* this is indexed addressing mode with a scale of 4 (int = 4 bytes) */

		"	movl	(%rdi,%esi,4),%ecx				  		\n"

		/* all done, standard epilogue */
		"	movq	%rbp,%rsp					  			\n"
		"	pop		%rbp						  			\n"
		"	ret							  					\n"
		"	.size	partition,.-partition				  		\n"
	);

//================================================
// void quickSortRec(int data[],int low,int high)
//

asm(	"	.text							  				 \n"
		"	.globl	quickSortRec					  		 \n"
		"	.type	quickSortRec,@function					 \n"

		"quickSortRec:							 			 \n"
		"	push	%rbp						  		 	 \n"
		"	movq	%rsp,%rbp					  		 	 \n"

	/* subtract from rsp to make space for temps */
		"	subq	$16,%rsp					  		 	 \n"
	/* some equates to remember locations */
		"	hole	.equ	-12					  			 \n"
		"	low		.equ	-4					  		 	 \n"
		"	high	.equ	-8					  		 	 \n"

	/* save low and high since we will clobber them in partition */
		"	movl	%esi, low(%rbp)					 		 \n"
		"	movl	%edx, high(%rbp)					 	 \n"

	/* call partition. the parms are all set up already */
		"	call	partition					 					 \n"
	/* save return value */
		"	movl	%eax,hole(%rbp)							 \n"

	/* recurse with low and (hole-1) as low and high */

	/* set up second parm */
		"	movl	low(%rbp),%esi					  		 \n"
	/* set up third parm */
		"	movl	%eax,%edx					 			 \n"
		"	decl	%edx									 \n"
	
		"	call	quickSortRec								 \n"

	/* recurse with (hole+1) and high as low and high */

	/* all done, standard epilogue */
		"	movq	%rbp,%rsp					 			 \n"
		"	pop		%rbp									 \n"
		"	ret							 					 \n"
		"	.size	quickSortRec,.-quickSortRec			  	 \n"
	);

//================================================
// void quickSort(int data[],int nItems)
//

void quickSort(int [],int);

asm(	"	.text							 				 \n"
	"	.globl	quickSort					 				 \n"
	"	.type	quickSort,@function				 			 \n"

	"	push	%rbp						 				 \n"
	"	movq	%rsp,%rbp					 				 \n"
	/*  first parm already set up */
	/* third parm is nItems-1 */
	"	movl	%esi,%edx					 				 \n"
	"	decl	%edx										 \n"
	/* set up second parm as 0 */
	"	xorl	%esi,%esi					  					 \n"
	"	call	quickSortRec					  				 \n"

	/* all done, standard epilogue */
	"	movq	%rbp,%rsp					  				\n"
	"	pop	%rbp						  					\n"
	"	ret							 						\n"
	"	.size	quickSort,.-quickSort				  			\n"
	);

int main(void) {
  int nItems,i;

  // ... read data, get count

  // sort the list
  quickSort(data,nItems);

  // output the list
  for (i=0;i<nItems;i++)
    printf("%d\n",data[i]);

  return 0;
}

