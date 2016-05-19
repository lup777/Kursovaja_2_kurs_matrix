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
  //display_matrix(matrix, matrix_size);
  
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
/*
void sort_matrix2(int**& matrix, size_t size)
{
  int line; //индекс по горизонтали
  int column; // индекс по вертикали
  int prev; //индекс перед column
  int next; // индекс следующий за prev
  int center = size / 2;
  int center_shift;
  int flag = 0;;

  
  if((size % 2) != 0)
    {
      cout << "odd matrix" << endl;
      cout << "center = " << center << endl;
    }
  else
    {
      center --;
      cout << "even matrix" << endl;
      cout << "center = " << center << " " << center + 1 << endl;
    }

  if((size % 2) != 0) //если не чётная матрица
    {
      for(line = 0; line < size; line ++)
	{
	  flag = 1;

	  if(line >= center) // если уже прошли середину матрицы по вертикали - то половина ширины ромба в этой строке есть ширина матрицы - номер строки
	    center_shift = size - line - 1;
	  else // если еще не прошли середину матрицы по вертикали, то половина ширины ромба в этой строке есть номер строки.
	    center_shift = line;
	
	  while(flag != 0) // пока не отсортируем всю строку
	    {
	      flag = 0;
	      prev = size - 2;
		  
	      for(column = size - 1; // начнём с конца строки
		  prev > 0; // идём от конца до начала
		  column --) // один проход сортировки по всей строке
		{

		  next = column;
		  prev = column - 1;
		  		  
		  if( prev == center + center_shift ) // если prev указывает на  правую грань ромба
		    {
		      prev = center - center_shift - 1; // перешагиваем его (точка перед левой гранью ромба)
		      //next = prev; // а эта точка следующая сразу за правой гранью ромба
		      column = center - center_shift; // на левой грани куба (в конце итерации из него вычтется 1)
		    }
		  else if( (prev < center + center_shift) &&
			   (prev >= center - center_shift))
		    { //это если сходу попали внуть ромба, т.е. мы в середине ромба
		      flag = 0;
		      break;
		    }
		  
		  //cout << "matrix[" << line << "][" << column << "]" << endl;
		  if( matrix[line][prev] < matrix[line][next] )
		    {
		      int tmp = matrix[line][prev];
		      matrix[line][prev] = matrix[line][next];
		      matrix[line][next] = tmp;
		      flag = 1;
		    }
		}
	    }
	}
    }
  else //чётная матрица 
    {
      for(line = 0; line < size; line ++)
	{
	  flag = 1;

	  if(line >= center) // если уже прошли середину матрицы по вертикали - то половина его ширины в этой строке есть ширина матрицы - номер строки
	    center_shift = size - line - 1;
	  else // если еще не прошли середину матрицы по вертикали, то половина ширины ромба в этой строке есть номер строки.
	    center_shift = line;
   
	  while(flag != 0) // делаем проходы сортировки пока не отсортируем всю строку
	    {
	      flag = 0;
	      prev = size - 2; // -2 = ( -1 индекс массива с нуля) + (-1 предыдущй индекс)
		  
	      for(column = size - 1; // начнём с конца строки
		  prev > 0; // идём от конца до начала
		  column --) // один проход сортировки по всей строке
		{

		  next = column;
		  prev = column - 1;
		  		  
		  if( prev == center + center_shift + 1 ) // если prev указывает на  правую грань ромба
		    {
		      prev = center - center_shift - 1; // перешагиваем его (точка перед левой гранью ромба)
		      //next = prev; // а эта точка следующая сразу за правой гранью ромба
		      column = center - center_shift; // на левой грани куба (в конце итерации из него вычтется 1)
		    }
		  else if( (prev < center + center_shift + 1) &&
			   (prev >= center - center_shift) )
		    {
		      flag = 0;
		      break;
		    }

		  if( matrix[line][prev] < matrix[line][next] )
		    {
		      int tmp = matrix[line][prev];
		      matrix[line][prev] = matrix[line][next];
		      matrix[line][next] = tmp;
		      flag = 1;
		    }
		}
	    }
	}
    }
}

*/
void sort_matrix2(int**& matrix, size_t size)
{
  int center = size / 2;
  printf("center = %d\n", center);

    if((size % 2) != 0)
    {
      cout << "odd matrix" << endl;
      cout << "center = " << center << endl;
    }
  else
    {
      center --;
      cout << "even matrix" << endl;
      cout << "center = " << center << " " << center + 1 << endl;
    }

    
    if( (size % 2) != 0 ) //если матрица не чётная
      {
	// СОРТИРУЕМ ВЕРХНИЙ ПРАВЫЙ УГОЛ МАТРИЦЫ
	for (int line = 0; line < center; line ++) // выбираем последовательно строки матрицы для сортировки
	  {
	    int flag = 1;
	    while(flag != 0) // сортируем текущую строку пока не отсортируем её полностью
	      {
		flag = 0; // пока ни одной пары элементов не поменяли местами
		for (int column = size - 1; column - 1 > center + line; column --) // один проход по всеё строке пока
		  {
		    printf("line = %d, column = %d \n", line, column);
		    if (matrix[line][column] < matrix[line][column - 1]) // сортируем 2 текущих елемента
		      {
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;  // поменяли местами пару элементов, значит надо будет ещё раз проётись по этой строке
		      } // if
		  }// for
	      } // while(flag ....
	  } // for (int line = 0.....
	
	// СОРТИРУЕМ НИЖНИЙ ПРАВЫЙ УГОЛ МАТРИЦЫ
	for (int line = center; line < size; line ++)
	  {
	    int flag = 1;
	    while(flag != 0) // сортируем текущую строку пока не отсортируем её полностью
	      {
		flag = 0; // пока ни одной пары элементов не поменяли местами
		for (int column = size - 1; column - 1 > (center - 1) + (size - line); column --)
		  {
		    printf("line = %d, column = %d \n", line, column);
		    if (matrix[line][column] < matrix[line][column - 1])
		      {
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;
		      }
		  }
	      }
	  }
	/*
	// СОРТИРУЕМ ВЕРХНИЙ ЛЕВЫЙ УГОЛ МАТРИЦЫ
	for (int line = 0; line < center; line ++) // выбираем последовательно строки матрицы для сортировки
	  {
	    int flag = 1;
	    while(flag != 0) // сортируем текущую строку пока не отсортируем её полностью
	      {
		flag = 0; // пока ни одной пары элементов не поменяли местами
		for (int column = size - 1; column - 1 > center + line; column --) // один проход по всеё строке пока
		  {
		    printf("line = %d, column = %d \n", line, column);
		    if (matrix[line][column] < matrix[line][column - 1]) // сортируем 2 текущих елемента
		      {
			int tmp = matrix[line][column - 1];
			matrix[line][column - 1] = matrix[line][column];
			matrix[line][column] = tmp;
			flag = 1;  // поменяли местами пару элементов, значит надо будет ещё раз проётись по этой строке
		      } // if
		  }// for
	      } // while(flag ....
	  } // for (int line = 0.....
	*/
      }   
}

void clean_romb(int**& matrix, size_t matrix_h_size)
{
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
      }
}
