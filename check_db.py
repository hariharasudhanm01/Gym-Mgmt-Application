import sqlite3

def check_db():
    print("\n--- CHECKING SQLITE DATABASE (gym_management.db) ---")
    try:
        conn = sqlite3.connect('gym_management.db')
        cursor = conn.cursor()
        
        tables = ['Users', 'Members', 'Trainers', 'WorkoutPlans', 'HealthProgress', 'TrainerRatings']
        
        for table in tables:
            print(f"\n[{table}] table contents:")
            try:
                cursor.execute(f"SELECT * FROM {table}")
                rows = cursor.fetchall()
                if not rows:
                    print("  (empty)")
                else:
                    columns = [description[0] for description in cursor.description]
                    print("  | " + " | ".join(columns) + " |")
                    for row in rows:
                        print("  | " + " | ".join(str(cell) for cell in row) + " |")
            except sqlite3.OperationalError as e:
                print(f"  Error reading table {table}: {e}")
                
        conn.close()
    except Exception as e:
        print(f"Database error: {e}")

if __name__ == "__main__":
    check_db()
