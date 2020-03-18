#pragma once

#ifndef __FUNC_H__
#define __FUNC_H__

Line* Add_new_Line();
void Print_all_line(Line * head_line);
void esc_menu_print_out();
void Get_esc(int point, char **copy_temp,Line *head_line);
Line* Select_line(Line * head_line);
void Insert_selected_line(Line *pointing_line);
void Delete_selected_line(Line *head_line, Line *pointing_line);
char* Copy_selected_line(Line *pointing_line);
void Paste_selected_line(char *copy_temp, Line *pointing_line);
void main_input_loop(Line * head_line);
/*SIMPLE_FUNCTION*/
void clear_buf();
int get_keyboard();
char* get_string_return_ptr();
#endif

#ifdef NOTYET
void Add_doubly_node_First(Node* head_node, int item);
void Add_Line_Last(Line * head_node, char *temp)
void Print_doubly_node(Node *head_node);
void SI_doubly_node_Left(Node* head_node, int item, int Insert_Left);
void SI_doubly_node_Right(Node* head_node, int item, int Insert_Right);
void Delete_doubly_node(Node *head_node, int item);
int Count_doubly_node(Node *head_node);
#endif
