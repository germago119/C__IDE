//
// Created by Roger Valderrama on 3/30/18.
//

#ifndef C_IDE_CODEEDITOR_HPP
#define C_IDE_CODEEDITOR_HPP


#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;

class QResizeEvent;

class QSize;

class QWidget;

class LineNumberArea;


class CodeEditor : public QPlainTextEdit {
Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);

    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void updateLineNumberAreaWidth(int newBlockCount);

    void highlightCurrentLine();

    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget {
public:
    explicit LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return {codeEditor->lineNumberAreaWidth(), 0};
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};


#endif //C_IDE_CODEEDITOR_HPP
