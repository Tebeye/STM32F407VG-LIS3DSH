class RingBuffer:
    def __init__(self,size_max):
        self.max = size_max
        self.data = []

    class __Full:
        def append(self, x):
            """ Append an element overwriting the oldest one. """
            self.data[self.cur] = x
            self.cur = (self.cur+1) % self.max
        def get(self):
            return self.data[self.cur:]+self.data[:self.cur]

    def append(self,x):
        self.data.append(x)
        if len(self.data) == self.max:
            self.cur = 0
            self.__class__ = self.__Full

    def get(self):
        return self.data

