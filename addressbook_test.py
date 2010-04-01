#!/usr/bin/env python

from socket import *
from addressbook_pb2 import *
import time

sock = socket( AF_INET, SOCK_DGRAM )

msg = AddressBook()
person = msg.person.add()
person.name = 'J Doe'
person.id = 12345
person.email = 'j@doe.net'
phone = person.phone.add()
phone.number = '123-456-7890'
phone.type = 0
phone = person.phone.add()
phone.number = '111-111-1111'
phone.type = 1

running = True

while running:
    try:
        sock.sendto( msg.SerializeToString(), ("233.0.0.1",33445) )
        time.sleep( 10 )
    except KeyboardInterrupt:
        running = False
        continue
        
    
