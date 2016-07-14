#ifndef NEWSVISITOR_H_
#define NEWSVISITOR_H_

class NewspaperNews;
class TwitterNews;

class NewsVisitor
{
public:
   virtual ~NewsVisitor() {};

   virtual void visit(const NewspaperNews* news) = 0;
   virtual void visit(const TwitterNews* news) = 0;
};

#endif
