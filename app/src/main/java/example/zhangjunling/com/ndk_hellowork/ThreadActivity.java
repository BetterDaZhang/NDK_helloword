package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class ThreadActivity extends AppCompatActivity {

    private EditText mThreadCountView;
    private EditText mIterationCountView;
    private Button mStartThreadView;
    private TextView mMessageView;


    static{
        System.loadLibrary("nativethreads");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread);
        nativeInit();
        initView();;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeFree();
    }

    private void initView() {
        mThreadCountView = (EditText) this.findViewById(R.id.et_thread_count_id);
        mIterationCountView = (EditText) this.findViewById(R.id.et_iterations_count_id);
        mMessageView = (TextView) this.findViewById(R.id.tv_message);
        mStartThreadView = (Button) this.findViewById(R.id.bt_start_thread);
        mStartThreadView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int threadsCount = Integer.valueOf(mThreadCountView.getText().toString().trim());
                int iterations = Integer.valueOf(mIterationCountView.getText().toString().trim());
                if(threadsCount > 0 && iterations > 0){
                    startThread(threadsCount,iterations);
                }
            }
        });
    }

    private void onNativeMessage(final String message){
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mMessageView.append(message);
                mMessageView.append("\n");
            }
        });
    }

    private void startThread(int threadsCount, int iterations) {
//        javaThread(threadsCount, iterations);
        posixThreads(threadsCount,iterations);
    }

    private void javaThread(final int threadsCount, final int iterations){
        for(int i = 0; i < threadsCount; i++){
            final int threadId = i;
            new Thread(){
                @Override
                public void run() {
                    nativeWork(threadId, iterations);
                }
            }.start();
        }
    }

    public native void nativeInit();
    public native void nativeFree();
    public native void nativeWork(int threads,int iterations);
    public native void posixThreads(int threads,int iterations);
}
