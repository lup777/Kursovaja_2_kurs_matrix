#include <stdio.h>
#include <alloca.h>
#include <iostream>

#define FAILED 1
#define SUCCESS 0

using namespace std;

typedef struct INDEX
{
  int curr;
  int prev;
} index_t;

void display_matrix(int**& matrix, size_t size);
void fill_matrix_with_random_value(int**& matrix, size_t size);
void sort_matrix2(int**& matrix, size_t size);
bool prepare_next_index(index_t&  index, size_t h_size, size_t v_size, int v_index);
void clean_romb(int**& matrix, size_t matrix_h_size);

int main()
{
  size_t matrix_h_size; // размер массива по горизонтали
  size_t matrix_v_size; // размер масива по вертикали
  size_t matrix_size; // размернолсть квадратной матрицы

  cout<<"\nHello!\n";
  cout<<"Please, enter matrix dimension:\n";
  cin>>matrix_size;
  matrix_v_size = matrix_h_size = matrix_size;

  // выделяем память под указатели на столбцы матрицы (matrix_h_size)(один горизонтальный массив)
  int **matrix = new int*[ matrix_size ];  
  
  if(matrix == NULL)
    {
      cout<<"failed to allocat memory for matrix\n";
      return FAILED;
    }

  if((matrix_size % 2) != 0)
    {
      cout<<"matrix should be even"<<endl;
      return FAILED;
    }
  
  if(matrix_size < 5)
    {
      cout<<"matrix is too small"<<endl;
      return FAILED;
    }

  if(matrix_size > 40)
    {
      cout<<"Matrix is too big"<<endl;
      return FAILED;
    }
  
  for(int i = 0; i < matrix_size; i++)
    {
      //выделяем память под столбцы матрицы (одномерные вертикальные массивы)
      matrix[i] = new int[ matrix_size ];

      if( matrix[i] == NULL )
	{
	  printf("failed to allocat memory for matrix[%d]\n", i);
	  return FAILED;
	}
    }

  printf("memory for matrix %dx%d allocated\n", matrix_size, matrix_size);
  
  fill_matrix_with_random_value(matrix, matrix_size);
  display_matrix(matrix, matrix_size);

  sort_matrix2(matrix, matrix_size);
  display_matrix(matrix, matrix_size);
  
  clean_romb(matrix, matrix_h_size);
  display_matrix(matrix, matrix_size);
  
  for(int i = 0; i < matrix_size; i++)
    {
      delete [] matrix[i];
    }
  
  delete [] matrix;

  cout<<"\nGoodBy!\n";
  return SUCCESS;
}

void display_matrix(int**& matrix, size_t size)
{
  int line, column;
  
  cout<<"display matrix\n\n";

  for( line = 0; line < size; line++ )
    {
      for( column = 0; column < size; column++ )
	{
	  printf("%3d ", matrix[line][column]);
	}
      printf("\n\n");
    }
}

void fill_matrix_with_random_value(int**& matrix, size_t size)
{
  int i, j, k = 1;
  cout<<"fill matrix\n...\n";
  
  for( i = 0; i < size; i++ )
    {
      for( j = 0; j < size; j++ )
	{
	  if (j%2 == 0)
	    
	    {
	      matrix[i][j] = i + k;
	      k++;
	    }
	  else
	    {
	      matrix[i][j] = i + k + 6;
	      k++;
	    }
	}
    }
}

void sort_matrix2(int**& matrix, size_t size)
{
  int center = size / 2;
  printf("center = %d\n", center);

    if((size % 2) != 0)
    {
      cout << "odd matrix" << endl;
      cout << "Please, choose even matrix size "<< endl;
      return;
    }
  else
    {
      center --;
      cout << "even matrix" << endl;
      //cout << "center = " << center << " " << center + 1 << endl;
    }

    
    if( (size % 2) == 0 ) //если матрица чётная
      {
	// СОРТИРУЕМ ВЕРХНЮЮ ПОЛОВИНУ
	for (int line = 0; line < center; line ++) // выбираем последовательно строки матрицы для сортировки
	  {
	    int flag = 1;
	    while(flag != 0) // сортируем текущую строку пока не отсортируем её полностью
	      {
		flag = 0; // пока ни одной пары элементов не поменяли местами
		// СОРТИРУЕМ ПРАВЫЙ ВЕРХНИЙ УГОЛ
		for (int column = size - 1; column - 1 > center + line; column --) // один проход по всеё строке пока
		  {
		    if (matrix[line][column] < matrix[line][column - 1]) // сортируем 2 текущих елемента
		      {
			//printf("line = %d, column = %d \n", line, column);
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;  // поменяли местами пару элементов, значит надо будет ещё раз проётись по этой строке
		      } // if
		  }// for
		// СОРТИРУЕМ ЛЕВЫЙ ВЕРХНИЙ УГОЛ
		for (int column = center - line; column - 1 >= 0; column --) // один проход по всеё строке пока
		  {
		    if (matrix[line][column - 1] < matrix[line][column]) // сортируем 2 текущих елемента
		      {
			//printf("line = %d, column = %d \n", line, column);
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;  // поменяли местами пару элементов, значит надо будет ещё раз проётись по этой строке
		      } // if
		  }// for
	      } // while(flag ....
	  } // for (int line = 0.....
	
	// СОРТИРУЕМ НИЖНЮЮ ПОЛОВИНУ
	for (int line = center; line < size; line ++)
	  {
	    int flag = 1;
	    while(flag != 0) // сортируем текущую строку пока не отсортируем её полностью
	      {
		flag = 0; // пока ни одной пары элементов не поменяли местами
		// СОРТИРУЕМ ПРАВЫЙ НИЖНИЙ УГОЛ
		for (int column = size - 1; column - 1 > (center - 1) + (size - line); column --)
		  {
		    if (matrix[line][column] < matrix[line][column - 1])
		      {
			//printf("line = %d, column = %d \n", line, column);
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;
		      }
		  }
		// СОРТИРУЕМ ЛЕВЫЙ НИЖНИЙ УГОЛ
		for (int column = center - (size - line) + 1; column - 1 >= 0; column --)
		  {
		    if (matrix[line][column - 1] < matrix[line][column])
		      {
			//printf("line = %d, column = %d \n", line, column);								
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;
		      }
		  }
	      }
	  }
     }   
}

void clean_romb(int**& matrix, size_t /*matrix_h_*/size)
{/*
  int center = matrix_h_size/2;
  int c = center;
  int v_index, h_index;
  
  if (matrix_h_size%2 == 0)
    {
      for(v_index = 0; v_index < matrix_h_size + 1; ++v_index)
	
	for(h_index = v_index; h_index < matrix_h_size - v_index; ++h_index)
	  {
	    matrix[(matrix_h_size/2) - v_index - 1][h_index] = 0;
	    matrix[v_index + (matrix_h_size/2)][h_index] = 0;
	  }
    }
  else
    for (v_index = 0; v_index < matrix_h_size; ++v_index)
      {
	for (h_index = center; h_index < c+1; ++h_index)
	  matrix[v_index][h_index] = 0;
	
	if ((c < matrix_h_size-1) && (v_index < matrix_h_size/2))
	  {
	    ++c;
	    --center;
	  }
	else
	  {
	    --c;
	    ++center;
	  }
	  }*/
  int center = size / 2;

  // ОЧИЩАЕМ ВЕРХНЮЮ ПОЛОВИНУ
  for (int line = 0; line < center; line ++)
    {
      for (int column = center - line; column < center + line; column ++)
	{
	  matrix[line][column] = 0;
	}
    }
  //ОЧИЩАЕМ НИЖНЮЮ ПОЛОВИНУ
  for (int line = center; line < size; line ++)
    {
      for (int column = center - (size - line) + 1; column < center + (size - line) - 1; column ++)
	{
	  matrix[line][column] = 0;
	}
    }
}
