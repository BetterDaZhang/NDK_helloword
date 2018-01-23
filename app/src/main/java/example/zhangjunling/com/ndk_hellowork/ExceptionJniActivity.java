package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class ExceptionJniActivity extends AppCompatActivity {

    private TextView mContentView;
    private Button mExceptionButton;
    private Button mDoExceptoinButton;

    static {
        System.loadLibrary("exception");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exception_jni);

        mContentView = this.findViewById(R.id.tv_content);
        mExceptionButton = this.findViewById(R.id.bt_exception);
        mDoExceptoinButton = this.findViewById(R.id.bt_do_exception);

        mExceptionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mContentView.setText(exceptionHelloWord());
            }
        });
        mDoExceptoinButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                doExceptionTest();
            }
        });
    }

    public static void exceptionCallback() {
        int a = 20 / 0;
        Log.d("zhangjunling", "--->" + a);
    }

    public static void normalCallback() {
        Log.d("zhangjunling", "In Java: invoke normalCallback.");
    }

    public native String exceptionHelloWord();
    public native void doExceptionTest();

    public static native void staticExceptionTest();

}
