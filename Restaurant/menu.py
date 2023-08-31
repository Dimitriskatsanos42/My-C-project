import os
from tabulate import tabulate
from datetime import datetime

class Restaurant:
    def __init__(self) -> None:
        self.menu=[
            ("Chicken Burger", "Burger με κοτόπουλο, bacon, τυρί edam, τομάτα, μαρούλι με μαγιονέζα", 4.20 ),
            ("Ham Burger", "Burger με μπιφτέκι, τυρί, κέτσαπ, μουστάρδα", 2.85),
            ("Green Burger", "Burger με ζουμερό μπιφτέκι, τυρί, φρέσκια τομάτα, μαρούλι,κρεμμύδι, πίκλες, κέτσαπ και dressing sauce",4.20),
            ("Club Sandwich", "Club sandwich με 3 πλούσιες στρώσεις Philadelphia σε φρυγανισμένο ψωμί του τοστ με ζουμερό κοτόπουλο φιλέρο, bacon, τομάτα, μαρούλι και τηγανητές πατάτες",10.90),
            ("Σαλάτα ceasar’s", "Δροσερή πράσινη σαλάτα με ζουμερό κοτόπουλου σε βάση μαρουλιού, με καλαμπόκι, κρουτόν, τριμμένο τυρί και vinaigrette ελαιόλαδου",6.90),
            ("Κινόα με Λαχανικά", "Δροσερή σαλάτα με κινόα, κόκκινη πιπεριά, τοματίνια, αγγούρι, δυόσμο, φρέσκο μαϊντανό και sauce λαδολέμονο.", 6.30)
        ]
        self.order_id=1
        self.orders=dict()
        self.history=dict()
    
    def payment(self):
        pass
        
    def main_menu(self,modify=False):
        print('\n\nΕπιλογές:')
        print('==========')
        print(f'1. {"Εναρξη" if not modify else "Τροποποιήση"} Παραγγελίας')
        print('2. Εμφάνιση παραγγελίας')
        print('3. Αφαίρεση προιόντος από παραγγελία')
        print('4. Πληρωμή')
        ch=input('Εισάγετε την επιλογή:')
        if not ch.isdigit():
            raise ValueError(f'{ch} is not a digit')

        ch=int(ch)
        if ch==1:
            new_order_item='y'
            while new_order_item=='y':
                for idx,(name,_,_) in enumerate(self.menu):
                    print(f'Επιλογή #{idx}: {name}')
                menu_item=input('Εισάγετε αριθμό προιόντος από μενού:')
                quantity=input('Εισάγετε ποσότητα:')
            
                if not menu_item.isdigit():
                    raise ValueError('munu_item input is not digit!!! Please provide a digit')

                if not quantity.isdigit(): 
                    raise ValueError('munu_item input is not digit!!! Please provide a digit')

                self.orders[self.order_id].append((int(menu_item),int(quantity)))

                new_order_item=input('Επιθυμείτε να εισάγεται άλλο προιόν(y/n):')

        elif ch==2:
            print(tabulate(tabular_data=[[idx+1,self.menu[order_item][0],quantity,self.menu[order_item][2],self.menu[order_item][2]*quantity] for idx,(order_item,quantity) in enumerate(self.orders[self.order_id])],headers=['α/α','ΟΝΟΜΑ','ΤΜΧ','ΤΙΜΗ ΤΜΧ','ΑΞΙΑ']))
            os.system('pause')
            
        elif ch==3:
            print(tabulate(tabular_data=[[idx+1,self.menu[order_item][0],quantity,self.menu[order_item][2],self.menu[order_item][2]*quantity] for idx,(order_item,quantity) in enumerate(self.orders[self.order_id])],headers=['α/α','ΟΝΟΜΑ','ΤΜΧ','ΤΙΜΗ ΤΜΧ','ΑΞΙΑ']))
            print('-'*6)
            removal_item=input('Επιλέξτε γραμμή προιόντος προς αφαίρεση:')
            if not removal_item.isdigit():
                raise ValueError('Removal item mus be digit')
            
            removal_item=int(removal_item)
            if removal_item>0 and removal_item<=len(self.orders[self.order_id]):
                item=self.orders[self.order_id].pop(removal_item-1)
                print(f'Το προιόν {item} αφαιρέθηκε επιτυχώς από την παραγγελία')
            else:
                print(f'Το προιόν με κωδικό γραμμής {item} δεν βρέθηκε στην λίστα παραγγελίας')
            os.system("pause")

        elif ch==4:
            print(tabulate(tabular_data=[[idx+1,self.menu[order_item][0],quantity,self.menu[order_item][2],self.menu[order_item][2]*quantity] for idx,(order_item,quantity) in enumerate(self.orders[self.order_id])],headers=['α/α','ΟΝΟΜΑ','ΤΜΧ','ΤΙΜΗ ΤΜΧ','ΑΞΙΑ']))
            confirm=input('Παρακαλώ επιβεβαιώστε την αγορά(y/n):')
            if confirm=='v':
                print(f'Παρακαλώ πληρώστε {sum([self.menu[item_id][2]*qnt for item_id,qnt in self.orders[self.order_id]])}')
                print('Σας ευχαριστούμε για την αγορά σας!')
                if self.order_id not in self.history:
                    self.history[self.order_id]=list()
                self.history[self.order_id].append(self.orders[self.order_id])
                self.orders.pop(self.order_id)
            os.system("pause")

    def register(self):
        table_id=input(f'Παρακαλώ εισάγετε αριθμό τραπεζιού(0-20):')
        if table_id in self.orders:
            print(f"Στο τραπέζι {table_id} πραγματοποιήτε τρέχουσα παραγγελία")
        
        if not table_id.isdigit():
            print(f'Η επιλογή {table_id} δεν είναι έγκυρη!!!!')
            return False
        self.order_id=int(table_id)
        self.orders[self.order_id]=list()
        return True
    
    def modify(self):
        table_id=input('Παρακαλώ εισάγετε αριθμό τραπεζιού που θέλετε να επεξεργαστείτε:')
        if int(table_id) not in self.orders:
            print(f'Το τραπέζι {table_id} δεν βρίσκετε στην λίστα με τα διαθέσιμα τραπέζια')
            return False

        self.order_id=int(table_id)
        return True

    def mainloop(self):
        while True:
            os.system('cls' if os.name == 'nt' else 'clear')
            print('Επιλογές:')
            print('==========')
            print('1. Έναρξη Παραγγελίας')
            print('2. Εμφάνιση παραγγελίας')
            print('3. Αφαίρεση προιόντος από παραγγελία')
            print('4. Πληρωμή')
            ch=input('Επιλέξτε:')
            mod=False
            if int(ch)==1:
                validity=self.register()
            elif int(ch)==2:
                validity=self.modify()
                mod=True
            else:
                break
            if not validity: continue
            self.main_menu(modify=mod)

if __name__=='__main__':
    restaurant=Restaurant()
    restaurant.mainloop()
        

