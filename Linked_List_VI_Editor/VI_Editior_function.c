#include"ALL.h"

Line * Add_new_Line()
{
	Line *temp;
	temp = (Line *)malloc(sizeof(Line));
	temp->string = NULL;
	temp->L_Next = NULL;
	temp->R_Next = NULL;

	return temp;
}

void Add_Line_Last(Line * head_line)
{
	Line *temp = Add_new_Line();
	Line *pointing_line = head_line;
	temp->string = get_string_return_ptr();

	if (pointing_line->R_Next == NULL)
	{
		pointing_line->R_Next = temp;
		pointing_line->R_Next->L_Next = temp;
		pointing_line->R_Next->R_Next = temp;
	}
	else
	{
		pointing_line = pointing_line->R_Next;

		pointing_line->L_Next->R_Next = temp;
		temp->L_Next = pointing_line->L_Next;
		pointing_line->L_Next = temp;
		temp->R_Next = pointing_line;
	}
}
void Print_all_line(Line * head_line)
{
	Line *pointing_line = head_line;

	if (pointing_line->R_Next == NULL)
	{
		system("cls");
	}
	else
	{
		pointing_line = pointing_line->R_Next;
		while (pointing_line->R_Next != head_line ->R_Next)
		{
			printf("%s\n", pointing_line->string);
			pointing_line = pointing_line->R_Next;
		}
		printf("%s\n", pointing_line->string);
	}
}

void main_input_loop(Line * head_line)
{
	int point;
	char *copy_temp;
	while (1)
	{
		Add_Line_Last(head_line);
		system("cls");
		Print_all_line(head_line);
		puts("계속 입력: enter\n메뉴 진입: esc\n프로그램 종료: q");
		point = get_keyboard();
		if (point == 27)
		{
			esc_menu_print_out();
			point = get_keyboard();
			Get_esc(point, &copy_temp, head_line);
		}
		else if (point == 'q')
			break;
		else
			point = '\0';

	}
}
void esc_menu_print_out()
{
	puts("기능 설명");
	puts("i: 삽입");
	puts("x: 삭제");
	puts("y: 복사");
	puts("p: 붙이기");
	puts("esc: 기능 나가기");
	puts("선택:");
}

Line* Select_line(Line * head_line)
{
	Line *pointing_line = head_line;
	int point;

	if (pointing_line->R_Next == NULL)
	{
		system("cls");
	}
	else
	{
		//아쉬운점 우리가 원래 쓰고 있는 편집기 같이 물 흐르듯이 작성할 수 있게 만들고 싶다
		//현재 문자를 입력받는 함수를 변형해서 중간에 받아들이는 문자를 체크 할 수 있게 만들면 좀더 우리가 쓰는 편집기에 가까워 질것 같음
		//저장 불러오기 등등도 넣으면 좀더 가까워 질듯
		puts("선택하려면 enter 다른 줄 선택 화살표 위 아래");
		pointing_line = pointing_line->R_Next;
		while (1)
		{
			printf("%s\n", pointing_line->string);
			point = get_keyboard();
			if (point == 72)
			{
				pointing_line = pointing_line->L_Next;
			}

			else if (point == 80)
			{
				pointing_line = pointing_line->R_Next;
			}
			else if (point == 13)
				break;
		}
		puts("선택된 라인");
		printf("%s\n", pointing_line->string);
	}
	return pointing_line;
}

void Insert_selected_line(Line *pointing_line)
{
	Line *temp = Add_new_Line();
	temp->string = get_string_return_ptr();

	pointing_line->L_Next->R_Next = temp;
	temp->L_Next = pointing_line->L_Next;
	pointing_line->L_Next = temp;
	temp->R_Next = pointing_line;

}

void Delete_selected_line(Line *head_line, Line *pointing_line)
{
	if (pointing_line == head_line->R_Next)
	{
		head_line->R_Next = pointing_line->R_Next;
		pointing_line->L_Next->R_Next = pointing_line->R_Next;
		pointing_line->R_Next->L_Next = pointing_line->L_Next;
		free(pointing_line);
	}
	else
	{
		pointing_line->L_Next->R_Next = pointing_line->R_Next;
		pointing_line->R_Next->L_Next = pointing_line->L_Next;
		free(pointing_line);
	}
}

char* Copy_selected_line(Line *pointing_line)
{
	char *temp;
	temp = (char*)malloc((strlen(pointing_line->string) + 1) * sizeof(char));
	memcpy(temp, pointing_line->string, (strlen(pointing_line->string) + 1) * sizeof(char));
	return temp;
}

void Paste_selected_line(char *copy_temp, Line *pointing_line)
{
	Line *temp = Add_new_Line();

	temp->string = (char*)malloc((strlen(copy_temp) + 1) * sizeof(char));
	memcpy(temp->string, copy_temp, (strlen(copy_temp) + 1) * sizeof(char));

	pointing_line->L_Next->R_Next = temp;
	temp->L_Next = pointing_line->L_Next;
	pointing_line->L_Next = temp;
	temp->R_Next = pointing_line;
}

void Get_esc(int point, char **copy_temp, Line *head_line)
{
	switch (point)
	{
	case 105://i
		Insert_selected_line(Select_line(head_line));
		break;
	case 120://x
		Delete_selected_line(head_line, Select_line(head_line));
		break;
	case 121://y
		(*copy_temp) = Copy_selected_line(Select_line(head_line));
		break;
	case 112://p
		Paste_selected_line((*copy_temp), Select_line(head_line));
		break;
	case 27://esc
		break;
	}
}


/*SIMPLE_FUNCTION*/
void clear_buf()//버퍼 비우기
{
	while (getchar() != '\n');
}

int get_keyboard()//키 값을 받아서 반환 한다
{
	int point;

	while (1)
	{
		point = getch();
		if (point != 224)
			break;
	}

	return point;
}


char* get_string_return_ptr()//문자열의 길이에 따라서 능동적으로 배열의 할당 메모리를 조절하여 입력받는 함수
{
	//이 방식이 좀더 안정적일것 같은 느낌적인 느낌?
	//받아서 쓰는 방식이 좋을까 
	//내부에서 입력 받은 것을 리턴하는 방식이 좋을까?

	char *temp;
	unsigned int str_len = 2;//문자열의 길이 정보를 저장하고 있는 배열
	char ch = 0;
	unsigned int cnt = 0;


	temp = (char*)malloc(str_len * sizeof(char));

	while (ch != '\n')//입력 받은 문자가 엔터이면 바로 루프 탈출
	{
		if (str_len > cnt)
		{
			ch = getchar();
			temp[cnt] = ch;
			cnt++;
		}

		else
		{
			str_len += 5;
			temp = (char*)realloc(temp, (str_len) * sizeof(char));
		}
	}

	temp[cnt - 1] = '\0';
	str_len = strlen(temp);
	temp = (char*)realloc(temp, (str_len + 1) * sizeof(char));//엔터를 입력받은 경우에는 1바이트 메모리 할당

	cnt = 0;
	ch = 0;
	//정확하게 문자열의 형태로 저장
	//예를 들어 [123456\0]을 입력했으면 메모리 7바이트가 리턴
	//strlen시 6리턴
	//malloc는 7바이트 해줘야함
	return temp;
}
