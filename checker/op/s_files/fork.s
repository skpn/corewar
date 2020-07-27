.name "tester"
.comment "test fork"

#ld %30,r1
fork %65534
live %-1
fork %65534

#this will created the same process at the same place
