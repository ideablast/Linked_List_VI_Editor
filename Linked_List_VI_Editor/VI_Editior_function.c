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
		puts("��� �Է�: enter\n�޴� ����: esc\n���α׷� ����: q");
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
	puts("��� ����");
	puts("i: ����");
	puts("x: ����");
	puts("y: ����");
	puts("p: ���̱�");
	puts("esc: ��� ������");
	puts("����:");
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
		//�ƽ����� �츮�� ���� ���� �ִ� ������ ���� �� �帣���� �ۼ��� �� �ְ� ����� �ʹ�
		//���� ���ڸ� �Է¹޴� �Լ��� �����ؼ� �߰��� �޾Ƶ��̴� ���ڸ� üũ �� �� �ְ� ����� ���� �츮�� ���� �����⿡ ����� ���� ����
		//���� �ҷ����� �� ������ ���� ����� ����
		puts("�����Ϸ��� enter �ٸ� �� ���� ȭ��ǥ �� �Ʒ�");
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
		puts("���õ� ����");
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
void clear_buf()//���� ����
{
	while (getchar() != '\n');
}

int get_keyboard()//Ű ���� �޾Ƽ� ��ȯ �Ѵ�
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


char* get_string_return_ptr()//���ڿ��� ���̿� ���� �ɵ������� �迭�� �Ҵ� �޸𸮸� �����Ͽ� �Է¹޴� �Լ�
{
	//�� ����� ���� �������ϰ� ���� �������� ����?
	//�޾Ƽ� ���� ����� ������ 
	//���ο��� �Է� ���� ���� �����ϴ� ����� ������?

	char *temp;
	unsigned int str_len = 2;//���ڿ��� ���� ������ �����ϰ� �ִ� �迭
	char ch = 0;
	unsigned int cnt = 0;


	temp = (char*)malloc(str_len * sizeof(char));

	while (ch != '\n')//�Է� ���� ���ڰ� �����̸� �ٷ� ���� Ż��
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
	temp = (char*)realloc(temp, (str_len + 1) * sizeof(char));//���͸� �Է¹��� ��쿡�� 1����Ʈ �޸� �Ҵ�

	cnt = 0;
	ch = 0;
	//��Ȯ�ϰ� ���ڿ��� ���·� ����
	//���� ��� [123456\0]�� �Է������� �޸� 7����Ʈ�� ����
	//strlen�� 6����
	//malloc�� 7����Ʈ �������
	return temp;
}
