/* iksemel (XML parser for Jabber)
** Copyright (C) 2000-2003 Gurer Ozen
** This code is free software; you can redistribute it and/or
** modify it under the terms of GNU Lesser General Public License.
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "iksemel.h"

int main (int argc, char *argv[])
{
	setlocale (LC_ALL, "");
	static char xml[] = "<test>"
						"<text>Hello, &#x4e16;&#x754c;</text>"
						"<emoji>&#x1f4a9;</emoji>"
						"<invalid></invalid>"
						"<null></null>"
						"<twoun>&#xc5;</twoun>"
						"<threeun>&#x100;</threeun>"
						"<katana>&#x30bb;</katana>"
						"<wideunicode>&#x26007;</wideunicode>"
						"<nonprint>&#x01;&#x07;&#x0b;&#x7f;</nonprint>"
						"<store>&#x645;&#x62e;&#x632;&#x646;</store>"
						"</test>";

	iks *x = iks_new ("test");
	iks_insert_cdata (iks_insert (x, "text"), "Hello, 世界", 13);
	iks_insert_cdata (iks_insert (x, "emoji"), "\U0001F4A9", 4);
	iks_insert_cdata (iks_insert (x, "invalid"), "\x80\x81", 2);
	iks_insert_cdata (iks_insert (x, "null"), "\0", 1);
	iks_insert_cdata (iks_insert (x, "twoun"), "Å", 3);
	iks_insert_cdata (iks_insert (x, "threeun"), "Ā", 3);
	iks_insert_cdata (iks_insert (x, "katana"), "セ", 4);
	iks_insert_cdata (iks_insert (x, "wideunicode"), "\U00026007", 4);
	iks_insert_cdata (iks_insert (x, "nonprint"), "\x1\a\v\x7F", 4);
	iks_insert_cdata (iks_insert (x, "store"), "\u0645\u062e\u0632\u0646", 8);

	char *t = iks_string (iks_stack (x), x);
	if(!t || strcmp(t, xml) != 0) {
		printf("Result:   %s\n", t);
		printf("Expected: %s\n", xml);
		return 1;
	}
	iks_delete(x);

	return 0;
}
