using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp5
{
    enum Direction
    {
        DOWN = -1,
        STAND = 0,
        UP = 1
    };
    enum State {Buisy, Free }
    class Controler
    {
        int floor;
        State state;
        List<int> destination;
        Direction direction;
        int maxfloor;

        public Func2 StartMoving; //Cabine call
       

        public Controler(int startfloor, int maxfloor)
        {
            floor = startfloor;
            this.maxfloor = maxfloor;
            destination = new List<int>();
            state = State.Free;
            direction = Direction.STAND;
        }
        public void AddNewFloor(int floor)
        {
            destination.Add(floor);
            FindNewDestination(floor);
        }
        public void FindNewDestination(int floor)
        {
            if (state == State.Buisy)
                return;

            int  newFloor = -5984;
            bool isNewFloorFound = false;

            if(destination.Count>0)
            {
                newFloor = destination[0];
                isNewFloorFound = true;
            }
            if (isNewFloorFound)
            {
                state = State.Buisy;
                if (this.floor > newFloor)
                    direction = Direction.DOWN;
                if (this.floor < newFloor)
                    direction = Direction.UP;
                StartMoving?.Invoke(newFloor, ((int)direction));
            }
            else
            {
                state = State.Free;
            }
        }

        public void LiftFree(int floor)
        {
            if (this.floor == floor - ((int)direction))
            {
                state = State.Free;
                direction = Direction.STAND;
                destination.Remove(floor);
                this.floor = floor;
           }
        }
        public void SkipFloor(int floor)
        {
            this.floor = floor;
            Console.WriteLine("We skip floor number " + Convert.ToString(this.floor));
        }
    }
}
