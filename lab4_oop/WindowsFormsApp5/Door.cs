using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace WindowsFormsApp5
{
    enum Status
    {
        OPEN,
        OPENING,
        CLOSING,
        CLOSED
    };
    class Door
    {
        TimerPlus WorkDoorTimer;
        Timer WaitDoorTimer;
        Timer emergency;
        Status doorstatus;

        public Func1 doorClosed;
        public Func1 doorIsClosedGUI, doorIsOpenedGUI, ClosingGUI, OpeningGUI;

        //все остановки таймеров надо убрать
        public Door()
        {
            doorstatus = Status.CLOSED;
            WorkDoorTimer = new TimerPlus(1000);
            WaitDoorTimer = new Timer(1500);
            emergency = new Timer();

            WaitDoorTimer.Elapsed += async (sender, e) => await Task.Run(() => startClosing());
            emergency.Elapsed += async (sender, e) => await Task.Run(() => open());

            WorkDoorTimer.AutoReset = false;
            WaitDoorTimer.AutoReset = false;
        
            //doorClosed += startOpening;
        }

        public void startOpening()
        {
            if (doorstatus != Status.CLOSED && doorstatus != Status.CLOSING)
                return;

            
            Console.WriteLine("Door is opening...");
            OpeningGUI?.Invoke();//GUI

            if (doorstatus == Status.CLOSED)
            {
                doorstatus = Status.OPENING;
                WorkDoorTimer.Elapsed += async (sender, e) => await Task.Run(() => open());
                WorkDoorTimer.Start();
                
            }
            else
            {
                //Этот кусок кода не работает и я не знаю почему. Если разберетесь, можете сказать
                doorstatus = Status.OPENING;
                double left = WorkDoorTimer.TimeLeft;
                WorkDoorTimer.Stop();
                emergency.Interval = 1000 - left;
                emergency.Start();
            }
            
        }

       private void open()
        {
            if (doorstatus != Status.OPENING)
                return;

            doorstatus = Status.OPEN;
            Console.WriteLine("Door is opened. Dear passengers! Go aboard!");

            WorkDoorTimer.Elapsed -= async (sender, e) => await Task.Run(() => open());
            WorkDoorTimer.Stop();
            emergency.Stop();
            WaitDoorTimer.Start();
            doorIsOpenedGUI?.Invoke();//GUI
        }

        public void startClosing()
        {
            if (doorstatus != Status.OPEN)
                return;

            doorstatus = Status.CLOSING;
            Console.WriteLine("Door is closing...");
            
            WorkDoorTimer.Elapsed += async (sender, e) => await Task.Run(() => close());
            WorkDoorTimer.Interval = 1000;
            WorkDoorTimer.Start();

            ClosingGUI?.Invoke();//GUI
        }


        private void close()
        {
            if (doorstatus != Status.CLOSING)
                return;

            doorstatus = Status.CLOSED;
            Console.WriteLine("Door is clossed");

            WorkDoorTimer.Elapsed -= async (sender, e) => await Task.Run(() => close());
            WorkDoorTimer.Stop();

            doorIsClosedGUI?.Invoke();//GUI
            doorClosed?.Invoke();
        }
        public void SetActionToGui(GuiActionDelegates actions)
        {
            doorIsClosedGUI += actions.CloseDoor;
            doorIsOpenedGUI += actions.OpenDoor;
            ClosingGUI += actions.ClosingDoor;
            OpeningGUI += actions.OpeningDoor;
        }

    }
}

public class TimerPlus : System.Timers.Timer
{
    private DateTime m_dueTime;

    public TimerPlus(int num) : base(num) => this.Elapsed += this.ElapsedAction;

    protected new void Dispose()
    {
        this.Elapsed -= this.ElapsedAction;
        base.Dispose();
    }

    public double TimeLeft => (this.m_dueTime - DateTime.Now).TotalMilliseconds;
    public new void Start()
    {
        this.m_dueTime = DateTime.Now.AddMilliseconds(this.Interval);
        base.Start();
    }

    private void ElapsedAction(object sender, System.Timers.ElapsedEventArgs e)
    {
        if (this.AutoReset)
            this.m_dueTime = DateTime.Now.AddMilliseconds(this.Interval);
    }
}