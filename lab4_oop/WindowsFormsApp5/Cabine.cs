using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Threading;

namespace WindowsFormsApp5
{

    delegate void Func(int a);

    delegate void Func1();

    delegate void Func2(int a, int b);

    enum CabineState
    {
        MOVES,
        STANDING
    };
    class Cabine
    {
        public Func1
            cabineStartMoving;//CabineMove
            
        public Func
            cabinePassingFloor,// Controller
            cabineOnFloorGUI,//GUI 
            cabineReachedDestinationFloor,//Gui + doorOpening
            CabineFree;//Controller

        int curfloor;
        int destfloor;

        Door door;

        CabineState state;
        System.Timers.Timer timer; //CabineMove

        public Cabine(int curfloor)
        {
            timer = new System.Timers.Timer(500);
            timer.Elapsed += async (sender, e) => await Task.Run(() => CabineMove());
            timer.AutoReset = false;
            this.curfloor = curfloor;
            destfloor = -676;
            state = CabineState.STANDING;
            door = new Door();

            cabineStartMoving += CabineMove;

            cabineReachedDestinationFloor += (int a) => door.startOpening();
            //cabineReachedDestinationFloor += (int a) => cabineStand(); //отключение дверей
            
            door.doorClosed += cabineStand;
        }

        public int direction { get; set; }

  
        public void cabineCall(int floor, int direction)
        {
            if (state != CabineState.STANDING)
                return;
            this.direction = direction;
            destfloor = floor;
            state = CabineState.MOVES;

            cabineStartMoving?.Invoke();
        }

        public void CabineMove()
        {

            if (state == CabineState.MOVES)
            {
                if (curfloor != destfloor)
                {
                    cabinePassingFloor?.Invoke(curfloor);//Controller
                    cabineOnFloorGUI?.Invoke(curfloor);
                    curfloor += direction;
                    timer.Start();
                }
                else
                {
                    cabineOnFloorGUI?.Invoke(curfloor);
                    cabineReachedDestinationFloor?.Invoke(curfloor);
                }
                
            }
            else
            {
                return;
            }
        }

        public void cabineStand()
        {
           if (state != CabineState.MOVES)
                return;
          
            state = CabineState.STANDING;
            timer.Stop();
            //Console.WriteLine("Lift stands on the floor " + Convert.ToString(floor));
            CabineFree(curfloor);
          
        }

        public void SetActionToGui(GuiActionDelegates actions)
        {
            cabineOnFloorGUI += actions.MoveAction;
            //cabineReachedDestinationFloor += actions.StopAction;
            CabineFree += actions.StopAction; 
            door.SetActionToGui(actions);
        }
    }
}
