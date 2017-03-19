package com.example.kevin_zhuang.watergoddemo;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    static {
        System.loadLibrary("WaterDispenser");
    }

    private EditText et;
    private EditText et2;
    private TextView tv;
    private String appendHead = "从VMC接收的消息：";
    private String liquid;
    private Button button2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        et = (EditText) findViewById(R.id.editText);
        et2 = (EditText) findViewById(R.id.editText2);
        tv = (TextView) findViewById(R.id.textview);

        button2 = (Button)findViewById(R.id.button2);
        button2.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                getInfo(0xFF);
                return true;
            }
        });
        tv.setMovementMethod(new ScrollingMovementMethod());
        tv.setText("水神售水机\n");
        tv.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("清除数据？");
                builder.setNegativeButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        tv.setText("");
                        dialog.dismiss();
                    }
                });
                builder.setNeutralButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                builder.create();
                builder.show();

                return false;
            }
        });

        Thread thread_protocol = new Thread(new Runnable() {
            @Override
            public void run() {
                Log.e("tag:","tag:");
                startProtocol();
            }
        });

        thread_protocol.start();

        final Handler mHandler = new Handler(getMainLooper()) {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 0xC1:
                        tv.append(appendHead+"VMC启动完成！");
                        tv.append("\n");
                        break;
                    case 0xA1:
                        byte[] machineIdByte = getRpt(2);
                        byte[] machineIdByte2 = new byte[machineIdByte.length-1];
                        Log.e(TAG,"machineIdByte.length="+machineIdByte.length);
                        System.arraycopy(machineIdByte,1,machineIdByte2,0,machineIdByte.length-1);
                        tv.append(appendHead+"机器编码: new String=" + (new String(machineIdByte2))+"=");
                        tv.append("\n");
                        tv.append(appendHead+"机器编码:bytes2HexString=" + bytes2HexString((getRpt(2)))+"=");
                        tv.append("\n");
                        break;
                    case 0xA2:
                        tv.append(appendHead+"固件版本号:bytes2HexString=" + bytes2HexString(getRpt(3)));
                        tv.append("\n");
                        tv.append(appendHead+"固件版本号: new String=" + (new String(getRpt(3)))+"=");
                        tv.append("\n");
                        break;
                    case 0xA3:
                        tv.append(appendHead + "脉冲数:new String=" + (new String(getRpt(4)))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "脉冲数:bytes2HexString=" + bytes2HexString(getRpt(4))+"=");
                        tv.append("\n");
                        break;
                    case 0xA4:
                        tv.append(appendHead + "单次购买水量上限制:new String=" + (new String(getRpt(5)))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "单次购买水量上限制:bytes2HexString=" + bytes2HexString(getRpt(5))+"=");
                        tv.append("\n");
                        break;
                    case 0xA5:
                        tv.append(appendHead + "总计出水量:String" + (new String(getRpt(6)))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "总计出水量:bytes2HexString=" + bytes2HexString(getRpt(6))+"=");
                        tv.append("\n");
                        break;
                    case 0xA6:
                        tv.append(appendHead + "购买水量等待时间:bytes2HexString=" + bytes2HexString(getRpt(7))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "购买水量等待时间:String=" + new String(getRpt(7))+"=");
                        tv.append("\n");
                        break;
                    case 0xA7:
                        tv.append(appendHead + "排水等待时间:bytes2HexString=" + bytes2HexString(getRpt(8))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "排水等待时间:String=" + new String(getRpt(8))+"=");
                        tv.append("\n");
                        break;
                    case 0xA8:
                        tv.append(appendHead + "所有值:bytes2HexString=" + bytes2HexString(getRpt(9))+"=");
                        tv.append("\n");
                        tv.append(appendHead + "所有值:String=" + new String(getRpt(9))+"=");
                        tv.append("\n");
                        break;
                    case 0xB1:
                        tv.append(appendHead + "销售状态:bytes2HexString=" + bytes2HexString(getStatusRpt(2))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "销售状态:String=" + new String(getStatusRpt(2))+"=");
                        tv.append("\n");
                        break;
                    case 0xB2:
                        tv.append(appendHead + "门开关:bytes2HexString=" + bytes2HexString(getStatusRpt(3))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "门开关:String=" +  new String(getStatusRpt(3))+"=");
                        tv.append("\n");
                        break;
                    case 0xB3:
                        liquid = bytes2HexString(getStatusRpt(4));
                        tv.append(appendHead + "原液低位:bytes2HexString=" + bytes2HexString(getStatusRpt(4))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "原液低位:String=" + new String(getStatusRpt(4))+"=");
                        tv.append("\n");
                        break;
                    case 0xB4:
                        tv.append(appendHead + "低水压:bytes2HexString=" + bytes2HexString(getStatusRpt(5))+"=");
                        tv.append("\n");

                        tv.append(appendHead + "低水压:String=" + new String(getStatusRpt(5))+"=");
                        tv.append("\n");
                        break;
                    case 0xB5:
                        tv.append(appendHead + "F2断开:" + bytes2HexString(getStatusRpt(6)));
                        tv.append("\n");
                        break;
                    case 0xB6:
                        tv.append(appendHead + "machineoutput1:" + bytes2HexString(getStatusRpt(7)));
                        tv.append("\n");
                        break;
                    case 0xB7:
                        tv.append(appendHead + "machineoutput2:" + bytes2HexString(getStatusRpt(8)));
                        tv.append("\n");
                        break;
                    case 0xD1:
                        tv.append(appendHead + "D1:出水成功后接收到的信息");
                        tv.append("\n");
                        break;
                }
            }
        };

        Thread thread_event = new Thread(new Runnable() {

            @Override
            public void run() {
                while (true) {
                    if (!(true)) break;
                    int i;
                    i = getEvent();
                    mHandler.sendEmptyMessage(i);
                }
            }
        });
        thread_event.start();
    }



    public static String bytes2HexString(byte[] b) {        //byte转16进制字符串函数
        String ret = "";
        for (int i = 0; i < b.length; i++) {
            String hex = Integer.toHexString(b[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            ret += hex.toUpperCase();
        }
        return ret;
    }


    public void getStatusButtonClicked(View view) {
        int type = Integer.parseInt(et.getText().toString());
        getStatus(type);
        tv.append("PC请求getStatus,类型" + type);
        tv.append("\n");
    }


    public void getInfoButtonClicked(View view) {
        int type = Integer.parseInt(et.getText().toString());
        getInfo(type);
        tv.append("PC请求getInfo,类型" + type);
        tv.append("\n");
    }

    public void setMachineIdButtonClicked(View view) {


//        byte machineId[] = {'1','1','1','1','1','1','1','1'};
        byte machineId[] = et.getText().toString().getBytes();
//        machineId[0] = 1;
//        machineId[1] = 1;
        Log.e("tag:","设置机器ID");
        setMachineID(machineId);
        tv.append("PC请求设置机器编号");
        tv.append("\n");
    }


    public void setFlowControlerButtonClicked(View view) {
        String getText = et.getText().toString();
//        byte waterFlow[] = et.getText().toString().getBytes();

//        byte waterFlow[] = {(byte)0x01,(byte)0x90};
        byte waterFlow[] = Integer.toHexString(Integer.parseInt(getText)).getBytes();


        //  String waterFlow = "12";

        setFlowControler(waterFlow);
        tv.append("PC请求设置脉冲流量计" + Arrays.toString(waterFlow));
        tv.append("\n");
    }


//    public void setMaxlitreButtonClicked(View view) {
//        byte waterLitre = 0x01;
//        setMaxLitre(waterLitre);
//        tv.append("PC请求设置购买水量上线" + waterLitre );
//        tv.append("\n");
//    }



    public void set1LButtonClicked(View view) {
        int nLitre;
        nLitre = 0x0A;
        Log.e("tag:", "出水1L");
        setVenderAction(nLitre);
    }

    public void set2LButtonClicked(View view) {
        int nLitre;
        nLitre = 0x14;
        setVenderAction(nLitre);
    }

    public void set3LButtonClicked(View view) {
        int nLitre;
        nLitre = 0x1a;
        setVenderAction(nLitre);
    }

    public void set4LButtonClicked(View view) {
        int nLitre;
        nLitre = 0x28;
        setVenderAction(nLitre);
    }

    public void set5LButtonClicked(View view) {
        char nLitre;
        nLitre = 0x32;
        setVenderAction(nLitre);
    }

    public void setLitreAndTimeButtonClicked(View view) {
        String litre = et.getText().toString();
        String time = et2.getText().toString();
        tv.append("PC请求设置水和时间" + " 水="+litre+" 时间="+time+" type=5、7\n");
//        tv.append("PC请求设置水和时间" + " 水=10"+" 时间=10"+" type=5、7\n");

        setMaxLitreAndTime(Byte.parseByte(litre),Byte.parseByte(time));
    }

    public void testLiquidButtonClicked(View view) {
        getStatus(4);
        new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
            @Override
            public void run() {
                tv.append(liquid);
            }
        }, 1000L);
    }






    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int getEvent();

    public native void getStatus(int m_type);

    public native void getInfo(int m_type);

    public native void setMachineID(byte[] machine_id);

    public native byte[] getMachineId();



    public native  byte[] getFlowControler();

//    public native  byte[] getMaxLitreAndTime();

    public native void setFlowControler(byte[] waterFlow);

    public native void setMaxLitreAndTime(byte Litre ,byte waterTime);

    public native byte[] getRpt(int rpt_type);

    public native byte[] getStatusRpt(int rpt_type);

    public native void setVenderAction(int nLitre);

    public native int startProtocol();

    public native void SetReset();


}
