#ifndef MYSQLHIGHLIGHTER_H
#define MYSQLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
//#include <QHash>
//#include <QTextCharFormat>

class QTextDocument;

class MySQLHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

public:
  MySQLHighlighter(QTextDocument *parent = 0);

protected:
  void highlightBlock(const QString &text);

private:
  struct HighlightingRule
  {
    QRegExp pattern;
    QTextCharFormat format;
  };
  QVector<HighlightingRule> highlightingRules;
  QStringList keywordPatterns;
  QStringList functionPatterns;
  QStringList datatypePatterns;
  QStringList charsetPatterns;
  QStringList numberAndOperatorPatterns;

  QRegExp commentStartExpression;
  QRegExp commentEndExpression;

  QTextCharFormat commentFormat;

  void fillKeywords();
  void fillFunctions();
  void fillDatatypes();
  void fillCharsets();
  void fillNumbersAndOperators();
};

#endif // MYSQLHIGHLIGHTER_H
