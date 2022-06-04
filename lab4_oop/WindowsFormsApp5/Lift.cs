using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp5
{
    
    class Lift
    {
        Cabine cabine;
        Controler controler;

        public Lift(int startfloor, int maxfloor)
        {
            cabine = new Cabine(startfloor);
            controler = new Controler(startfloor, maxfloor);

            controler.StartMoving += cabine.cabineCall;

            cabine.cabinePassingFloor += controler.SkipFloor;

            cabine.CabineFree += controler.LiftFree;
            cabine.CabineFree += controler.FindNewDestination;
        }
        public void call(int floor)
        {
            controler.AddNewFloor(floor);
        }

        public void SetActionToGui(GuiActionDelegates actions)
        { 
            //controler.StopMoving += actions.StopAction;
            cabine.SetActionToGui(actions);
        }
        
    }
}
