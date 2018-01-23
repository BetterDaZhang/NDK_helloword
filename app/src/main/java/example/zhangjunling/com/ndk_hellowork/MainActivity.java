package example.zhangjunling.com.ndk_hellowork;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button mHelloJniButton;
    private Button mExceptonJniButton;
    private Button mReferenceJniButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mHelloJniButton = this.findViewById(R.id.bt_view_hellojni);
        mExceptonJniButton = this.findViewById(R.id.bt_view_exception);
        mReferenceJniButton = this.findViewById(R.id.bt_view_reference);

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
    }
}
