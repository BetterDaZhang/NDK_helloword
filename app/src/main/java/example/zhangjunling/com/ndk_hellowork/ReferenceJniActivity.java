package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class ReferenceJniActivity extends AppCompatActivity {

    static {
        System.loadLibrary("reference");
    }

    private Button mLocalReferenceButton;
    private Button mGlobalReferenceButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reference_jni);

        mLocalReferenceButton = this.findViewById(R.id.bt_local_reference);
        mGlobalReferenceButton = this.findViewById(R.id.bt_global_reference);

        mLocalReferenceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String[] strings = getStrings(512,"I Love You %d Year！！！");
                for (String string : strings) {
                    System.out.println(string);
                }
            }
        });
        mGlobalReferenceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                initGlobalReference();
                Toast.makeText(ReferenceJniActivity.this,callGlobalReference(),Toast.LENGTH_SHORT).show();
            }
        });

    }

    public native String[] getStrings(int count, String sample);

    public native void initGlobalReference();
    public native String callGlobalReference();
}

