#!/bin/bash

NEWS_FILE=$1

cat ../data/ES_stopList.txt | tr [[:space:]] '\n' > /tmp/stopList.txt
gawk -v RS='( |[^[:space:][:alpha:]])+' '{printf "%s", sep $0; sep="\n"}' < $NEWS_FILE | grep  ^[A-Z] | tr [[:upper:]] [[:lower:]] > /tmp/mostMentionedList.txt

while IFS= read -r word;
do
   sed -ri "s/( |)\b$word\b//g" /tmp/mostMentionedList.txt;
done < /tmp/stopList.txt
sed -ni "/^$/!p" /tmp/mostMentionedList.txt

MOST_MENTIONED_ENTITY=`cat /tmp/mostMentionedList.txt | sort | uniq -c | sort -nr | head  -1 | awk '{print $2}'`

#rm -f /tmp/stopList.txt
#rm -f /tmp/mostMentionedList.txt

echo -e "The most mentioned entity in $NEWS_FILE is $MOST_MENTIONED_ENTITY"
