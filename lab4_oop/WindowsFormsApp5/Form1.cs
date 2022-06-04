using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace WindowsFormsApp5
{
    struct GuiActionDelegates
    {
        public Func MoveAction;
        public Func StopAction;
        public Func1 OpenDoor;
        public Func1 OpeningDoor;
        public Func1 CloseDoor;
        public Func1 ClosingDoor;
    }
    public partial class Form1 : Form
    {

        Lift lift;
        Button[] buttons;
        GuiActionDelegates actionstruct;
        List<string> queqwue;
        Func buttonpushed;
        public Form1()
        {
            InitializeComponent();
            queqwue = new List<string>();
            lift = new Lift(1, 12);
            buttonpushed += lift.call;
            actionstruct = new GuiActionDelegates()
            {
                MoveAction = InWhatFloor,
                StopAction = LiftStopped,
                OpenDoor = DoorOpened,
                OpeningDoor = DoorOpening,
                CloseDoor = DoorClosed,
                ClosingDoor = DoorClosing
            };

            lift.SetActionToGui(actionstruct);
            
            buttons = new Button[12];
            for(int i = 0; i < 12; i++)
            {
                buttons[i] = new Button();
                buttons[i].Location = new Point(button13.Location.X,button13.Location.Y+50 + 30*i);
                buttons[i].Margin = new Padding(4, 5, 4, 5);
                buttons[i].Name = Convert.ToString(i+1);
                buttons[i].Size = button13.Size;
                buttons[i].TabIndex = i+1;
                buttons[i].Text = Convert.ToString(i + 1);
                buttons[i].UseVisualStyleBackColor = true;
                buttons[i].Click += new EventHandler(button_Click);
                buttons[i].BackColor = Color.White;
                this.Controls.Add(buttons[i]);
            }
            buttons[0].BackColor = Color.Green;
        }

        private void DoorOpening()
        {
            if (button13.InvokeRequired)
            {
                var d = new Func1(DoorOpening);
                button13.Invoke(d);
            }
            else
            {
                button13.BackColor = Color.OrangeRed;
               // MessageBox.Show("Opening");
                button13.Text = "Opening";
 
            }
        }
        private void DoorOpened()
        {
            if (button13.InvokeRequired)
            {
                var d = new Func1(DoorOpened);
                button13.Invoke(d);
            }
            else
            {
                button13.BackColor = Color.Gold;
                button13.Text = "Opened";
            }
        }
        private void DoorClosing()
        {
            if (button13.InvokeRequired)
            {
                var d = new Func1(DoorClosing);
                button13.Invoke(d);
            }
            else
            {
                button13.BackColor = Color.Red;
                button13.Text = "Closing";
            }
        }
        private void DoorClosed()
        {
            if (button13.InvokeRequired)
            {
                var d = new Func1(DoorClosed);
                button13.Invoke(d);
            }
            else
            {
                button13.BackColor = Color.Blue;
                button13.Text = "Closed";
            }
        }

        private void LiftStopped(int floor)
        {
            //InWhatFloor(floor);
            
            if (buttons[floor - 1].InvokeRequired)
            {
                var d = new Func(LiftStopped);
                buttons[floor - 1].Invoke(d, floor);
            }
            else
            {
                buttons[floor - 1].Enabled = true;
                buttons[floor - 1].BackColor = Color.Orange;
                queqwue.Remove(Convert.ToString(floor));
                label2.Text = "";
                foreach (string s in queqwue)
                {
                    label2.Text += " " + s;
                }
            }

        }

        private void InWhatFloor(int floor)
        {
            foreach(Button b in buttons)
            {
                b.BackColor = Color.White;
            }
            buttons[floor - 1].BackColor = Color.Green;
        }

        private void button_Click(object sender, EventArgs e)
        {
            string s = "Lift called to" + Convert.ToString(((Button)sender).TabIndex) + "floor";
            Console.WriteLine(s);
            buttons[((Button)sender).TabIndex - 1].Enabled = false;
            queqwue.Add(Convert.ToString(((Button)sender).TabIndex));
            label2.Text = "";
            foreach (string s1 in queqwue)
            {
                label2.Text += " " + s1;
            }
            buttonpushed?.Invoke(((Button)sender).TabIndex);
            //lift.call(((Button)sender).TabIndex);
        }

      

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

    }
}
