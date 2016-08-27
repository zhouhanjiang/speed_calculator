# -*- coding: utf-8 -*-
"""
Created on Wed Aug 24 11:20:18 2016

@author: xtao
"""

import time

class speed_calculator:
    """Simple Speed Calculator"""
    
    def __init__(self):
        self.m_slots = [0, 0]
        self.m_last_update_time = 0
        self.m_total_bytes = 0
        
    def update(self, update_bytes):
        now = int(time.time())
        idx = now & 0x1
        if now == self.m_last_update_time:
            self.m_slots[idx] += update_bytes
        else:
            self.m_slots[idx] = update_bytes
        
        self.m_last_update_time = now
        self.m_total_bytes += update_bytes
        
    
    def get_speed(self):
        now = int(time.time())
        idx = (now - 1) & 0x1
        if now - self.m_last_update_time > 1:
            return 0
        else:
            return self.m_slots[idx]
            

################## Test ##################
if __name__ == '__main__':
    import random
    calc = speed_calculator()
    c = 0
    while 1:
        r = random.randint(800000, 1000000)
        calc.update(r)
        c += 1
        
        # sleep 0.1 second
        time.sleep(0.1)
        
        if c % 10 == 0:
            # print speed every 1 second
            print calc.get_speed()
            
        if c > 100:
            # break after 10 seconds
            break
        