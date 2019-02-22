using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace op_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            timer1.Start();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
                (e.KeyChar != '.') && (e.KeyChar != '-'))
            {
                e.Handled = true;
            }
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
            if (e.KeyChar == '-' && (sender as TextBox).Text.Length > 0)
            {
                e.Handled = true;
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
                (e.KeyChar != '.') && (e.KeyChar != '-'))
            {
                e.Handled = true;
            }
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
            if (e.KeyChar == '-' && (sender as TextBox).Text.Length > 0)
            {
                e.Handled = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" || textBox2.Text == "")
            {
                return;
            }
            double x = Convert.ToDouble(textBox1.Text);
            double y = Convert.ToDouble(textBox2.Text);
            if ((x >= -1 && x <= 0 && y >= 0 && y <= 1) || (x >= 0 && y <= 0 && x * x + y * y <= 1))
            {
                textBox3.BackColor = Color.FromArgb(192, 255, 192);
                textBox3.Text = "This point is valid.";
            }
            else
            {
                textBox3.BackColor = Color.FromArgb(255, 192, 192);
                textBox3.Text = "This point is invalid.";
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            progressBar1.Step = 1;
            progressBar1.PerformStep();
            progressBar1.Step = -1;
            progressBar1.PerformStep();
            //if (progressBar1.Value == progressBar1.Maximum)
            //{
            //    progressBar1.Step = -1;
            //}
            //else if (progressBar1.Value == progressBar1.Minimum)
            //{
            //    progressBar1.Step = 1;
            //}
            //if (progressBar1.RightToLeftLayout && progressBar1.Value == progressBar1.Minimum)
            //{
            //    progressBar1.RightToLeft = RightToLeft.No;
            //    progressBar1.RightToLeftLayout = false;
            //}
            //else if (!progressBar1.RightToLeftLayout && progressBar1.Value == progressBar1.Minimum)
            //{
            //    progressBar1.RightToLeft = RightToLeft.Yes;
            //    progressBar1.RightToLeftLayout = true;
            //}
            //progressBar1.PerformStep();
        }
    }
}
