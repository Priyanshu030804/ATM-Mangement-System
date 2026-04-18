class Account:
    def __init__(self, acc_no, pin, balance=0):
        self.acc_no = acc_no
        self.pin = pin
        self.balance = balance

    def check_pin(self, pin):
        return self.pin == pin

    def deposit(self, amount):
        if amount <= 0:
            print("Amount must be positive!")
            return
        self.balance += amount
        print(f"₹{amount} deposited successfully!")

    def withdraw(self, amount):
        if amount <= 0:
            print("Amount must be positive!")
            return
        if amount > self.balance:
            print("Insufficient Balance!")
        else:
            self.balance -= amount
            print(f"₹{amount} withdrawn successfully!")

    def show_balance(self):
        print(f"Current Balance: ₹{self.balance}")

    def change_pin(self, old_pin, new_pin):
        if self.pin == old_pin:
            self.pin = new_pin
            print("PIN changed successfully!")
        else:
            print("Incorrect old PIN!")


class ATMSystem:
    def __init__(self):
        self.accounts = {}

    def create_account(self):
        acc_no = input("Enter Account Number: ")

        if acc_no in self.accounts:
            print("Account already exists!")
            return

        pin = input("Set PIN (4 digits): ")
        if not (pin.isdigit() and len(pin) == 4):
            print("Invalid PIN format!")
            return

        try:
            balance = float(input("Enter Initial Balance: "))
            if balance < 0:
                print("Balance cannot be negative!")
                return
        except ValueError:
            print("Invalid amount!")
            return

        self.accounts[acc_no] = Account(acc_no, pin, balance)
        print("Account created successfully!")

    def login(self):
        acc_no = input("Enter Account Number: ")
        pin = input("Enter PIN: ")

        if acc_no in self.accounts and self.accounts[acc_no].check_pin(pin):
            print("Login Successful!")
            self.account_menu(self.accounts[acc_no])
        else:
            print("Invalid credentials!")

    def transfer_money(self, sender):
        receiver_acc = input("Enter Receiver Account Number: ")

        if receiver_acc not in self.accounts:
            print("Receiver account not found!")
            return

        try:
            amount = float(input("Enter amount to transfer: "))
        except ValueError:
            print("Invalid amount!")
            return

        if amount <= 0:
            print("Amount must be positive!")
            return

        if amount > sender.balance:
            print("Insufficient balance!")
            return

        receiver = self.accounts[receiver_acc]

        sender.balance -= amount
        receiver.balance += amount

        print(f"₹{amount} transferred successfully to Account {receiver_acc}!")

    def account_menu(self, account):
        while True:
            print("\n--- ATM MENU ---")
            print("1. Check Balance")
            print("2. Deposit")
            print("3. Withdraw")
            print("4. Transfer Money")
            print("5. Change PIN")
            print("6. Logout")

            choice = input("Enter choice: ")

            if choice == "1":
                account.show_balance()

            elif choice == "2":
                try:
                    amount = float(input("Enter amount: "))
                    account.deposit(amount)
                except ValueError:
                    print("Invalid input!")

            elif choice == "3":
                try:
                    amount = float(input("Enter amount: "))
                    account.withdraw(amount)
                except ValueError:
                    print("Invalid input!")

            elif choice == "4":
                self.transfer_money(account)

            elif choice == "5":
                old_pin = input("Enter old PIN: ")
                new_pin = input("Enter new PIN: ")
                account.change_pin(old_pin, new_pin)

            elif choice == "6":
                print("Logged out!")
                break

            else:
                print("Invalid choice!")

    def main_menu(self):
        while True:
            print("\n=== ATM SYSTEM ===")
            print("1. Create Account")
            print("2. Login")
            print("3. Exit")

            choice = input("Enter choice: ")

            if choice == "1":
                self.create_account()

            elif choice == "2":
                self.login()

            elif choice == "3":
                print("Thank you for using ATM!")
                break

            else:
                print("Invalid choice!")


# Run the system
atm = ATMSystem()
atm.main_menu()
