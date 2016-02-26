class Datastructure:

    def __init__(self):
        self.data_list = []
        self.name_list = []

        self.leader = int
        self.least = int

        self.is_in_order_points = False
        self.is_in_order_names = False

    def mergesort(self, sortable, comparison_target):

        if len(sortable) >1:
            mid = len(sortable)//2
            left = sortable[:mid]
            right = sortable[mid:]

            self.mergesort(left, comparison_target)
            self.mergesort(right, comparison_target)

            i=0
            j=0
            k=0

            while i < len(left) and j < len(right):
                if comparison_target == 1:
                    if left[i][comparison_target] > right[j][comparison_target]:
                        sortable[k] = left[i]
                        i=i+1
                    elif left[i][comparison_target] < right[j][comparison_target]:
                        sortable[k] = right[j]
                        j=j+1
                    else:
                        if left[i][2] > right[j][2]:
                            sortable[k] = left[i]
                            i = i+1
                        else:
                            sortable[k] = right[j]
                            j=j+1
                    k=k+1

                else:
                    if left[i][comparison_target] < right[j][comparison_target]:
                        sortable[k] = left[i]
                        i=i+1
                    else:
                        sortable[k] = right[j]
                        j=j+1
                    
                    k=k+1

            while i < len(left):
                sortable[k] = left[i]
                i=i+1
                k=k+1

            while j < len(right):
                sortable[k] = right[j]
                j=j+1
                k=k+1

        


    def add(self, nickname, bus_count, passenger_count):
        addable = [nickname, bus_count, passenger_count]
        self.data_list.append(addable)
        self.name_list.append(addable)
        self.is_in_order_points = False
        self.is_in_order_names = False


    def print(self):
        if self.is_in_order_points == False:

            self.mergesort(self.data_list, 1)
            self.leader = 0
            self.least = len(self.data_list)

            self.best_and_worst_are_known = True
            self.is_in_order_points = True

        for i in range (0, len(self.data_list)):
            print(str(i+1)+ ". "+ str(self.data_list[i][0])+ ": " + str(self.data_list[i][1]) + " buses, " + str(self.data_list[i][2])+ " passengers")

    def print_by_name(self):
        if self.is_in_order_names == False:

            self.mergesort(self.name_list, 0)
            self.is_in_order_names = True

        for i in range (0, len(self.name_list)):
            print(str(self.name_list[i][0])+ ": " + str(self.name_list[i][1]) + " buses, " + str(self.name_list[i][2])+ " passengers")

    def best(self):
        if self.is_in_order_points == True:
            print(str(1)+ ". "+ str(self.data_list[self.leader][0])+ ": " + str(self.data_list[self.leader][1]) + " buses, " + str(self.data_list[self.leader][2])+ " passengers")

    def worst(self):
        if self.is_in_order_points == True:
            print(str(self.least)+ ". "+ str(self.data_list[self.least-1][0])+ ": " + str(self.data_list[self.least-1][1]) + " buses, " + str(self.data_list[self.least-1][2])+ " passengers")

    def empty(self):
        self.data_list = []
        self.name_list = []

    def search(self, name):
        for i in range (len(self.data_list)):
            if str(self.data_list[i][0]) == name:
                print(str(i+1   )+ ". "+ str(self.data_list[i][0])+ ": " + str(self.data_list[i][1]) + " buses, " + str(self.data_list[i][2])+ " passengers")
                return
        print("Player "+ name +" was not found.")

    def size(self):
        return len(self.data_list)