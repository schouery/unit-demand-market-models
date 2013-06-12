Unit-Demand Market Models
=========================

We have three models for generating instances for Unit-Demand markets (also known as Multi-Unit Auctions). They are better described in a upcoming paper from Cristina G. Fernandes, Carlos E. Ferreira, Álvaro J. P. Franco and Rafael C. S. Schouery. We will update this document as soon we have a link for the paper.

The code is written in C++ and we believe that can be compiled in almost any system. 

File Format
-----------

    <BIDDERS> <ITEMS> <VALUATIONS>
    <content of valuation 0>
    <content of valuation 1>
    ...	
    <content of valuation VALUATIONS - 1>

    where <content of valuation k> (k between 1 and VALUATIONS - 1) represents:
    <BIDDER> <ITEM> <VALUE>

EXAMPLE
-------

    5 3 8
    0 0 121.848
    0 1 163.992
    1 0 1244.48
    1 2 195.299
    3 0 165.016
    3 1 225.806
    4 0 12.89
    4 2 13.6852

In this instance, we have 5 bidders, 3 items and 8 positive valuations.

Item 0 has value 121.848 for bidder 0 and value 1244.48 for bidder 1. Item 1 has value 163.992 for bidder 0 and value 0 for bidder 1. And so forth.


INSTANCES
---------

Inside the folder **instances** we have two subfolder, one called **small** and other called **large**. The folder called small contains instances with 50, 100, ..., 300 items (and the same size of bidders) and the folder called large contains instances with 1000, 1500, ..., 3000 items (and the same size of bidders).

Inside this subfolder we have three folders, one for each model. And inside each model folder we have the instances in the file format described before. 

We use the followin naming convention for our instances: the name starts with a letter (in small caps) that is the first letter of the name of the model (that is 'c' if it is the Characteristic model, 'n' if it is the Neighborhood model and 'p' if it is the Popularity model). And afterwards the name denotes the parameters used for generating this instance. Finally, at the end, we identify the number of this instance (because we have 20 instances with the same parameters).

For example, instance p-n=150-e=1200-q=200-d=0.25.15 was generated using the popularity model using the following command

    ./popularity -n 150 -e 1200 -q 200 -d 0.25

and it was the 15th instance generated according to this parameters. 

Also, inside the subfolders small and large, one can find the results for our empirical tests in tex and pdf formats.