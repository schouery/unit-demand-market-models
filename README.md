Unit-Demand Market Models
=========================

We have three models for generating instances for Unit-Demand markets (also known as Multi-Unit Auctions). They are better described in a upcoming paper from Cristina G. Fernandes, Carlos E. Ferreira, Álvaro J. P. Franco and Rafael C. S. Schouery. We will update this document as soon we have a link for the paper.

The code is written in C++ and we belive that can be compiled in almost any system. 

File Format
-----------

`<BIDDERS GROUPS> <ITEMS> <VALUATIONS>

<SIZE OF BIDDER GROUP 0>
	
<SIZE OF BIDDER GROUP 1>
...
<SIZE OF BIDDER GROUP (BIDDERS GROUPS - 1)>	
<content of valuation 0>
<content of valuation 1>
...	
<content of valuation VALUATIONS - 1>`

where <content of valuation k> (k between 1 and VALUATIONS - 1) represents:
<BIDDER GROUP> <ITEM> <VALUE>

EXAMPLE
-------

`5 3 8
2
2
1
2
1
0 0 121.848
0 1 163.992
1 0 1244.48
1 2 195.299
3 0 165.016
3 1 225.806
4 0 12.89
4 2 13.6852`

In this instance, we have 5 bidders, 3 items and 8 positive valuations. Bidders groups 1, 2 and 4 have size 2 and bidders groups 3 and 5 have size 1.

Item 0 has value 121.848 for bidder group 0 and value 1244.48 for bidder group 1. Item 1 has value 163.992 for bidder group 0 and value 0 for bidder group 1.
