package java.awt;

import java.awt.event.*;
import kaffe.util.Ptr;

/**
 * NativeContainer - abstract root of all native containers
 *
 * Copyright (c) 1999
 *    Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 *
 */
abstract public class NativeContainer
  extends Container
{
	Ptr nativeData;

protected NativeContainer() {
	flags |= IS_ASYNC_UPDATED;
}

public void addNotify () {
	if ( nativeData == null ) {
		throw new AWTError( "native create failed: " + this);
	}

	// enable mapping of native events to Java Components
	AWTEvent.registerSource( this, nativeData);

	setNativeBounds( x, y, width, height);

	//children setBounds() require registered parent
	super.addNotify();

	initAttribs();

	Toolkit.cmnSetBackground( nativeData, bgClr.nativeValue);
	Toolkit.cmnSetForeground( nativeData, fgClr.nativeValue);
	Toolkit.cmnSetFont( nativeData, font.nativeData);
	Toolkit.cmnSetCursor( nativeData, cursor.type);		
}

void cleanUpNative() {
	if ( nativeData != null ) {
		AWTEvent.unregisterSource( this, nativeData);
		nativeData = null;
	}
}

void createNative() {
}

void destroyNative () {
	if ( nativeData != null ) {
		Toolkit.cmnDestroyWindow( nativeData);
		cleanUpNative();
	}
}

ClassProperties getClassProperties() {
	return ClassAnalyzer.analyzeAll( getClass(), true);
}

public Graphics getGraphics () {
	if ( (flags & IS_ADD_NOTIFIED) != 0 )
		return NativeGraphics.getGraphics( null, nativeData, NativeGraphics.TGT_TYPE_WINDOW, 0,0,
	                                   0, 0, width, height, fgClr, bgClr, font, false);
	else
		return null;
}

Ptr getNativeData() {
	return nativeData;
}

Ptr getParentData() {
	for ( Container c=parent; c != null; c=c.parent) {
		if ( c instanceof NativeContainer ) {
			NativeContainer nc = (NativeContainer)c;
			return nc.nativeData;
		}
	}
	return null;
}

public void hide () {
	if ( (flags & IS_VISIBLE) != 0 ) {
		super.hide();

		if ( nativeData != null )
			Toolkit.cmnSetVisible( nativeData, false);
	}
}

void initAttribs() {
	boolean pv;

	if ( bgClr == null ) {
		pv = ( (parent != null) && (parent.bgClr != null) );
		setBackground( pv ? parent.bgClr : Defaults.WndBackground);
	}
	if ( fgClr == null ) {
		pv = ( (parent != null) && (parent.fgClr != null) );
		setForeground( pv ? parent.fgClr : Defaults.WndForeground);
	}
	if ( font == null ) {
		pv = ( (parent != null) && (parent.font != null) );
		setFont( pv ? parent.font : Defaults.WndFont);
	}
}

public void paint ( Graphics g ) {
	for ( int i=nChildren-1; i>=0; i-- ) {
		Component c = children[i];

		if ( c.getNativeData() != null ) 
			continue;

		if ( (c.flags & IS_VISIBLE) != 0) 
			g.paintChild( c, (flags & IS_IN_UPDATE) != 0);
	}
}

void kaffePaintBorder ( Graphics g, int left, int top, int right, int bottom ) {
}

void processMouse( MouseEvent e) {
	if ( Defaults.AutoPopup && e.isPopupTrigger() ) {
		triggerPopup( e.getX(), e.getY() );
	}
	super.processMouse( e);
}

public void processPaintEvent ( int id, int ux, int uy, int uw, int uh ) {
	NativeGraphics g = NativeGraphics.getClippedGraphics( null, this,
	                                               0,0,
	                                               ux, uy, uw, uh,
	                                               false);
	if ( g != null ){
		if ( id == PaintEvent.UPDATE ) {
			update( g);
		}
		else {
			paint( g);
		}
		g.dispose();
	}
}

public void removeNotify () {
	if ( nativeData != null ) {
		// generally components are destroyed native
		// via parent destruction. To prevent further event
		// emmitting ( esp. Paint events ) for unregistered compoments
		// ensure native destruction for dedicated component removes
		super.removeNotify();
		Toolkit.destroyNative( this);
	}
}

public void requestFocus() {
	super.requestFocus();

	if ( nativeData != null ) {
		Toolkit.cmnSetFocus( nativeData);
	}
}

public void reshape ( int xNew, int yNew, int wNew, int hNew ) {
	super.reshape( xNew, yNew, wNew, hNew);
	setNativeBounds( xNew, yNew, wNew, hNew);
}

public void setBackground ( Color clr ) {
	if ( clr != null ) {
		super.setBackground( clr);

		if ( nativeData != null ) {
			Toolkit.cmnSetBackground( nativeData, bgClr.nativeValue);
		}
	}
}

public void setCursor ( Cursor cursor ) {
	if ( cursor != null ) {
		this.cursor = cursor;
		setNativeCursor( cursor);
	}
}

public void setEnabled ( boolean isEnabled ) {
	super.setEnabled( isEnabled);

	if ( nativeData != null ) {
		Toolkit.cmnSetEnabled( nativeData, isEnabled);
	}
}

public void setFont ( Font newFont ) {
	if ( newFont != null ) {
		super.setFont( newFont);

		if ( nativeData != null ) {
			Toolkit.cmnSetFont( nativeData, font.nativeData);
		}
	}
}

public void setForeground ( Color clr ) {
	if ( clr != null ) {
		super.setForeground( clr);

		if ( nativeData != null ) {
			Toolkit.cmnSetForeground( nativeData, fgClr.nativeValue);
		}
	}
}

void setNativeBounds ( int x, int y, int width, int height ) {
	if ( nativeData != null ) {
		for ( Component c=parent; c != null; c = c.parent ) {
			if ( c instanceof NativeContainer )
				break;
			x += c.x;
			y += c.y;
		}
		Toolkit.cmnSetBounds( nativeData, x, y, width, height);
	}
}

void setNativeCursor ( Cursor cursor ) {
	if ( (nativeData != null) && ((flags & IS_ADD_NOTIFIED) != 0 )) {
		Toolkit.cmnSetCursor( nativeData, cursor.type);
	}
}

public void show () {
	if ( (flags & IS_VISIBLE) == 0 ) {
		super.show();

		if ( nativeData != null )
			Toolkit.cmnSetVisible( nativeData, true);
	}
}

public void update ( Graphics g) {
	flags |= IS_IN_UPDATE;
	g.clearRect( 0, 0, width, height);
	paint( g);
	flags &= ~IS_IN_UPDATE;
}
}
