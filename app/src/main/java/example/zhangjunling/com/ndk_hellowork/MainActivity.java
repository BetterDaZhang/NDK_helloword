package example.zhangjunling.com.ndk_hellowork;

import android.content.Intent;
import android.os.Bundle;
import android.os.Debug;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button mHelloJniButton;
    private Button mExceptonJniButton;
    private Button mReferenceJniButton;
    private Button mDebugButton;
    private Button mBionicButton;
    private Button mThreadButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mHelloJniButton = this.findViewById(R.id.bt_view_hellojni);
        mExceptonJniButton = this.findViewById(R.id.bt_view_exception);
        mReferenceJniButton = this.findViewById(R.id.bt_view_reference);
        mDebugButton = this.findViewById(R.id.bt_view_debug);
        mBionicButton = this.findViewById(R.id.bt_view_bionic);
        mThreadButton = this.findViewById(R.id.bt_view_thread);

        mHelloJniButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,HelloWordJniActivity.class));
            }
        });
        mExceptonJniButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,ExceptionJniActivity.class));
            }
        });
        mReferenceJniButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,ReferenceJniActivity.class));
            }
        });
        mDebugButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,DebugActivity.class));
            }
        });
        mBionicButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,BionicActivity.class));
            }
        });
        mThreadButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,ThreadActivity.class));
            }
        });
    }
}
