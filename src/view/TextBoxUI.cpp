#include "../../inc/view/TextBoxUI.h"

namespace Mitrais {
namespace UI {



TextBoxUI::TextBoxUI()
: buffer(nullptr)
, view(gtk_text_view_new())
{
	if(view != nullptr)
		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
}

TextBoxUI::~TextBoxUI()
{
	delete buffer;
	delete view;
}

void TextBoxUI::initialize()
{
	if(view != nullptr && buffer != nullptr)
	{
		gtk_text_buffer_create_tag(buffer, "gap","pixels_above_lines", 30, NULL);
		gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
		gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
		gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "gray", NULL);
		gtk_text_buffer_create_tag(buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
		gtk_text_buffer_create_tag(buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
	}
}

void TextBoxUI::setText()
{
	  gtk_text_buffer_insert(buffer, &iter, "Plain text\n", -1);

	  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Colored Text\n", -1, "blue_fg", "lmarg",  NULL);
	  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Text with colored background\n", -1, "lmarg", "gray_bg", NULL);
	  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Text in italics\n", -1, "italic", "lmarg",  NULL);
	  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Bold text\n", -1, "bold", "lmarg",  NULL);
}

GtkWidget* TextBoxUI::getGTKTextBox() const
{
	return view;
}

}
}
