/* iksemel (XML parser for Jabber)
** Copyright (C) 2000-2003 Gurer Ozen
** This code is free software; you can redistribute it and/or
** modify it under the terms of GNU Lesser General Public License.
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "iksemel.h"

int errors = 0;

void hex(char *dst, const char *s) {
	for (size_t i = 0; i < iks_strlen(s); i++) {
		sprintf(dst + (2 * i), "%02x", (unsigned char) s[i]);
	}

	dst[2 * iks_strlen(s)] = '\x00';
}

void validate_tag(const iks *document, const char *name, const char *expect) {
	iks *tag = iks_find((iks *) document, name);
	if (!tag) {
		printf("Cannot find tag %s\n", "text");
		errors++;

		return;
	}

	char *got = NULL;
	iks *child = iks_child(tag);
	if (child) {
		got = iks_cdata(iks_child(tag));
	}

	char expect_hex[1024];
	char got_hex[1024];

	hex(expect_hex, expect);
	hex(got_hex, got);

	if (iks_strcmp(expect_hex, got_hex) != 0) {
		printf("Incorrect value for %s: expected \"%s\", got \"%s\"\n",
			   name, expect_hex, got_hex);
		errors++;
	}
}

static void test_encode() {
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

	char *t = iks_string (iks_stack (x), x);
	if(!t || strcmp(t, xml) != 0) {
		printf("Result:   %s\n", t);
		printf("Expected: %s\n", xml);
		errors++;
	}
	iks_delete(x);
}

static void test_decode() {
	static char xml_dec[] = "<test>"
							"<text>Hello, &#x4e16;&#x754c; (world)</text>"
							"<emoji>&#x1F4A9;</emoji>"
							"<invalid>&#xG;&#;</invalid>"
							"<null></null>"
							"<twoun>&#xc5;</twoun>"
							"<threeun>&#x100;</threeun>"
							"<katana>&#12475;</katana>"
							"<wideunicode>&#x26007;</wideunicode>"
							"<nonprint>&#01;&#x07;&#x0b;&#x7f;</nonprint>"
							"<store>&#x645;&#x62e;&#x632;&#x646;</store>"
							"</test>";

	iks *x;
	iksparser *parser = iks_dom_new(&x);
	enum ikserror err = iks_parse(parser, xml_dec, 0, 1);
	if (err != IKS_OK) {
		printf("Error: %d\n", err);
		errors++;
		return;
	}
	iks_parser_delete(parser);

	validate_tag(x, "text", "Hello, 世界 (world)");
	validate_tag(x, "emoji", "\U0001F4A9");
	validate_tag(x, "invalid", "??");
	validate_tag(x, "null", NULL);
	validate_tag(x, "twoun", "Å");
	validate_tag(x, "threeun", "Ā");
	validate_tag(x, "katana", "セ");
	validate_tag(x, "wideunicode", "\U00026007");
	validate_tag(x, "nonprint", "\x1\a\v\x7F");
	validate_tag(x, "store", "\u0645\u062e\u0632\u0646");

	iks_delete(x);
}

int main (int argc, char *argv[])
{
	setlocale (LC_ALL, "");
	test_encode();
	test_decode();

	return errors;
}
