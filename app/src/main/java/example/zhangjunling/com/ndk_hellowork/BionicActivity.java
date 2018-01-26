package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class BionicActivity extends AppCompatActivity {

    static {
        System.loadLibrary("bionic");
    }

    private Button mProcessInteractionButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bionic);

        mProcessInteractionButton = this.findViewById(R.id.bt_process_interaction);

        mProcessInteractionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                processInteractoin();
            }
        });

    }
    public native void processInteractoin();
}
