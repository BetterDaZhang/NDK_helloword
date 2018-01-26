package example.zhangjunling.com.ndk_hellowork;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class DebugActivity extends AppCompatActivity {

    static {
        System.loadLibrary("breakdown");
    }

    private Button mBreakDownButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_debug);

        mBreakDownButton = this.findViewById(R.id.bt_breaddown);

        mBreakDownButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                helloWordBreadDown();
            }
        });
    }

    public native void helloWordBreadDown();

}
