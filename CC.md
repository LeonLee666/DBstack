# paper review

- 2PL在short transaction并且没有hotspot的场景下，性能好。一旦有hotspot或者long transaction的时候，性能下降严重。

## TICTOC

## SILO

## HEKATON [(VLDB11)](http://www.vldb.org/pvldb/vol5/p298_per-akelarson_vldb2012.pdf)
**每个transaction都会获取两个时间戳startTS和commitTS**。事物update新version的时候，先用startTS去填充oldVersion的engTS和newVersion的beginTS；在事务commit的时候，**用commitTS去替换startTS**。注意startTS的时间戳，同时担任了锁的职责。
基于OCC的多版本中，不需要单独的write phase。因为一旦事务commit后，用commitTS替换startTS后，update数据就对外可见。

## CICADA

## [Deuteronomy](http://justinlevandoski.org/papers/CIDR2011_Deuteronomy.pdf)
http://www.vldb.org/pvldb/vol8/p2146-levandoski.pdf

