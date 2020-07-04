// These functions order the centers of displayed objects so they
// can be drawn using the painters algorithm, necessary to support
// transparency.  

// Note that objid is not obj.id when drawing spheres.

    rglwidgetClass.prototype.getPieces = function(context, objid, subid, obj) {
      var n = obj.centers.length,
          depth,
          result = new Array(n);
      context = context.slice();
          
      for(i=0; i<n; i++) {
        z = this.prmvMatrix.m13*obj.centers[i][0] +
            this.prmvMatrix.m23*obj.centers[i][1] +
            this.prmvMatrix.m33*obj.centers[i][2] +
            this.prmvMatrix.m43;
        w = this.prmvMatrix.m14*obj.centers[i][0] +
            this.prmvMatrix.m24*obj.centers[i][1] +
            this.prmvMatrix.m34*obj.centers[i][2] +
            this.prmvMatrix.m44;
        depth = z/w;
        result[i] = {context: context, 
                     objid: objid,
                     subid: subid,
                     index: i, 
                     depth: depth};
      }
      return result;    
    };
    
    rglwidgetClass.prototype.getSpherePieces = function(context, objid, subid, obj, fastTransparency)
    {
      if (fastTransparency)
        if (subid === 0) 
          return this.getPieces(context, objid, -1, this.getObj(objid));
        else 
          return [];
      else
        return this.getPieces(context, objid, subid, obj);
    };
    
    rglwidgetClass.prototype.sortPieces = function(pieces) {
      var compare = function(i,j) {
        var diff = j.depth - i.depth;
        // We want to avoid context or obj changes,
        // so sort on those next.
        if (diff === 0) {
          var c1 = j.context.slice(),
              c2 = i.context.slice();
          diff = c1.length - c2.length; 
          while (diff === 0 && c1.length > 0) {
            diff = c1.pop() - c2.pop();
          }
          if (diff === 0)
            diff = j.objid - i.objid;
          if (diff === 0)
            diff = j.subid - i.subid;
        }
        return diff;
      }, result = [];
      if (pieces.length) {
        pieces = pieces.sort(compare);
        var i,
            thiscontext = pieces[0].context, 
            thisobjid = pieces[0].objid, 
            thissubid = pieces[0].subid,
            indices = [];
        for (i= 0; i < pieces.length; i++) {
          if (pieces[i].context !== thiscontext || 
              pieces[i].objid !== thisobjid ||
              pieces[i].subid !== thissubid) {
            result = result.concat({context: thiscontext, objid: thisobjid,
                                    subid: thissubid, indices: indices});
            thiscontext = pieces[i].context;
            thisobjid = pieces[i].objid;
            thissubid = pieces[i].subid;
            indices = [];
          }
          indices = indices.concat(pieces[i].index);
        }
        result = result.concat({context: thiscontext, objid: thisobjid,
                                subid: thissubid,
                                indices: indices});
      }
      return result;
    };
