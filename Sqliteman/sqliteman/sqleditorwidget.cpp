/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QPainter>

#include "sqleditorwidget.h"
#include "preferencesdialog.h"


SqlEditorWidget::SqlEditorWidget(QWidget * parent)
	: QTextEdit(parent)
{
}

void SqlEditorWidget::paintEvent( QPaintEvent* const e )
{
	QPainter p(viewport());

	// highlight current line
	if (PreferencesDialog::useActiveHighlighting())
	{
		QRect currLine = cursorRect();
		currLine.setLeft(0);
		currLine.setWidth(viewport()->width());
		p.fillRect(currLine, QBrush(PreferencesDialog::activeHighlightColor()));
	}

	// draw "max line lenght" mark
	if (PreferencesDialog::useTextWidthMark())
	{
		QFontMetrics fm(PreferencesDialog::sqlFont());
		int xpos = fm.width(QString(PreferencesDialog::textWidthMark()-1, 'X'));
		const QPen prevPen = p.pen();
		p.setPen(QPen(Qt::darkGreen, 1.0, Qt::DotLine));
		p.drawLine(xpos, 0, xpos, viewport()->height() - 1);
		p.setPen(prevPen);
	}
	p.end();
	QTextEdit::paintEvent(e);
}