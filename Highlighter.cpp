//
// Created by Roger Valderrama on 3/30/18.
//

#include "Highlighter.hpp"

Highlighter::Highlighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent) {

    //Colors
    auto byzantine = QColor::QColor(184, 51, 161, 255);
    auto blue = QColor::QColor(41, 52, 212, 255);
    auto persian = QColor::QColor(207, 49, 37, 255);
    auto green = QColor::QColor(0, 131, 18, 255);
    auto brown = QColor::QColor(119, 73, 45, 255);
    auto purple = QColor(111, 65, 167, 255);
    auto dandelion = QColor(255, 200, 20, 255);



    HighlightingRule rule;

    keywordFormat.setForeground(byzantine);
    //keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfloat\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";
            foreach (const QString &pattern, keywordPatterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

    //classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(purple);
    rule.pattern = QRegularExpression("\\breference<[A-Za-z]>");
    rule.format = classFormat;
    highlightingRules.append(rule);


    //classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(purple);
    rule.pattern = QRegularExpression("\\bstruct\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(green);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(dandelion);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    curlyFormat.setForeground(brown);
    rule.pattern = QRegularExpression("\\{|\\}");
    rule.format = curlyFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(persian);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    parentesisFormat.setForeground(persian);
    rule.pattern = QRegularExpression("\\(\\)");
    rule.format = parentesisFormat;
    highlightingRules.append(rule);

    numberFormat.setForeground(blue);
    rule.pattern = QRegularExpression(R"([0-9]\.|[0-9]+|\'[A-Za-z]\')");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::highlightBlock(const QString &text) {
            foreach (const HighlightingRule &rule, highlightingRules) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}