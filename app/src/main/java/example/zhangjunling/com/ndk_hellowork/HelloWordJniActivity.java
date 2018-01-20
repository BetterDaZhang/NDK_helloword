package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class HelloWordJniActivity extends AppCompatActivity {

    private TextView mContentTextView;
    private Button mHelloJniButton;
    private Button mStringButton;
    private Button mArrayButton;
    private Button mSetElementsArrayButton;
    private Button mGetRegionArrayButton;
    private Button mDirectByteBufferButton;
    private Button mGetDirectByteBufferButton;

    static {
        System.loadLibrary("helloworld");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hello_word_jni);

        mContentTextView = this.findViewById(R.id.tv_content);
        mHelloJniButton = this.findViewById(R.id.bt_hellojni);
        mStringButton = this.findViewById(R.id.bt_operateString);
        mArrayButton = this.findViewById(R.id.bt_array);
        mSetElementsArrayButton = this.findViewById(R.id.bt_set_element_array);
        mGetRegionArrayButton = this.findViewById(R.id.bt_get_region_array);
        mDirectByteBufferButton = this.findViewById(R.id.bt_directbytebuffer);
        mGetDirectByteBufferButton = this.findViewById(R.id.bt_directbytebuffer_set);

        mHelloJniButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String jniString = getStringFromJni();
                mContentTextView.setText(jniString);
            }
        });

        mStringButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mContentTextView.setText(operatorData("zhangjunling"));
            }
        });

        mArrayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] intArrayFromJni = getIntArrayFromJni();
                mContentTextView.setText(Arrays.toString(intArrayFromJni));
            }
        });
        mSetElementsArrayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mContentTextView.setText(Arrays.toString(setIntArrayToJni(new int[]{1,2,3,4,5})));
            }
        });
        mGetRegionArrayButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mContentTextView.setText(Arrays.toString(getRegionArrayFromJin()));
            }
        });
        mDirectByteBufferButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                byte[] datas = new byte[128];
                ByteBuffer directByteBufferFromJni = getDirectByteBufferFromJni();
//                for(int i = 0; i < 128; i++){
//                    Log.d("zhangjunling", "i:" + directByteBufferFromJni.get(i));
//                }
                directByteBufferFromJni.get(datas, 0, datas.length);
                mContentTextView.setText(Arrays.toString(datas));
            }
        });

        mGetDirectByteBufferButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                byte[] datas = new byte[128];
                for(int i = 0; i < 128; i++){
                   datas[i] = (byte)i;
                }
                setDirectByteBufferToJni(ByteBuffer.allocateDirect(128).put(datas));
            }
        });
    }

    public native String getStringFromJni();
    public native String operatorData(String operatData);

    public native int[] getIntArrayFromJni();
    public native int[] setIntArrayToJni(int[] data);

    public native int[] getRegionArrayFromJin();

    public native ByteBuffer getDirectByteBufferFromJni();
    public native void setDirectByteBufferToJni(ByteBuffer data);
}
