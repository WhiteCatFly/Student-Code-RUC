#ifndef KBHIT_H
#define KBHIT_H

#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef KBHIT_CPP
static struct termios initial_settings, new_settings;
static int peek_character = -1;
#endif

void InitKeyboard();
void CloseKeyboard();
void CheckKeyboard();

#endif
